// Fill out your copyright notice in the Description page of Project Settings.
#include "UE_World_Camera.h"
#include "CoordinateSystem.h"
#include "TileInfo.h"
#include "TileLoadManager.h"


// Sets default values
AUE_World_Camera::AUE_World_Camera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("OurCameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-90.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 40.f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);
	OurCamera->bUsePawnControlRotation = false;
	float defaultFOV = OurCamera->FieldOfView;
	OurCamera->FieldOfView = 120.0;

	OurCamera->SetActive(true);

	//控制默认玩家
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AUE_World_Camera::InitializeVirtualGlobe()
{
	//创建地球，球体
	//FVector radii = FVector(6378137.0, 6378137.0, 6356752.314245);
	FVector radii = SphereR;
	FRotator InRotation = FRotator(0.0, 0.0, 0.0);
	FVector InTranslation = SphereOrigin;
	FVector InScale3D = FVector(1.0, 1.0, 1.0);

	Sphere_CoordinateSystem earth3d_CoordinateSystem0 = Sphere_CoordinateSystem(radii,
		InRotation,
		InTranslation,
		InScale3D); 

	//设置相机初始位置
	FVector inPt0 = FVector(FMath::DegreesToRadians(114.30), FMath::DegreesToRadians(30.51), 10000.0);	

	FVector outPt0 = earth3d_CoordinateSystem0.ToUE_CoordinateSystem(inPt0);

	//更新相机位置
	//SetActorLocation(outPt0);

	this->UE_CameraState.FOV = 120.0;
	this->UE_CameraState.Location = outPt0;
	this->UE_CameraState.Rotator = FRotator(0.0, 0.0, 0.0);
	this->UE_CameraState.screenResolution = FVector2D(1920, 1080);
	this->UE_CameraState.AspectRatio = 2.0;

	
	//测试基于相机的瓦片调度逻辑
	this->sccts = SceneCulling_CenterTileStrategy(earth3d_CoordinateSystem0,this->UE_CameraState);
	this->tlm = TileLoadManager();

	
	

	//根据pt0加载
	//TSet<TileNode *> shouldLoadingTileSet = sccts.GetTilesShouldbeLoaded(currentCameraState, currentCameraState.screenResolution);

	//TSet<TileNode *> loadingTileSet = tlm.UpdateLoadingTileArray(shouldLoadingTileSet);
	//TSet<TileNode *> unLoadingTileSet = tlm.UpdateUnLoadingTileArray(shouldLoadingTileSet);

	//
	//loadingTileSet = tlm.UpdateLoadingTileArray(shouldLoadingTileSet);
	////需要维护tlm.loadedTileSet
	////tlm.loadedTileSet = loadingTileSet;
	//unLoadingTileSet = tlm.UpdateUnLoadingTileArray(shouldLoadingTileSet);
}

// Called when the game starts or when spawned
void AUE_World_Camera::BeginPlay()
{
	Super::BeginPlay();

	//初始化变量
	ScrollWheelSpeed = 1;
	//用于控制平移幅度的比率
	MoveStepFactor = 0.01;

	//球体的原点坐标
	this->SphereOrigin = FVector(0,0,0);

	//球体的半径
	//FVector SphereR = FVector(6378137.0, 6378137.0, 6356752.314245);
	this->SphereR = FVector(5000.0, 5000.0, 5000.0);
	this->MaxSphereR = FMath::Max3(SphereR.X, SphereR.Y, SphereR.Z);

	//地球的初始化
	InitializeVirtualGlobe();
}

// Called every frame
void AUE_World_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//若相机平移标识为true，调用CalcCameraMoveDragDirection完成操作逻辑
	if (IsMoveCameraState)
	{
		CalcCameraMoveDragDirection();
	}

	if (!MovementInput.IsZero())
	{
		MovementInput = MovementInput.GetSafeNormal();
		FVector newLocation = GetActorLocation();
		newLocation += GetActorForwardVector()*MovementInput.X;
		newLocation += GetActorRightVector()*MovementInput.Y;
		//SetActorLocation(newLocation);
	}

}

// Called to bind functionality to input
void AUE_World_Camera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//设置四个键盘按键用于控制精确的平移操作
	/*UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveForward", EKeys::W, 1.0f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveForward", EKeys::S, -1.0f));
	PlayerInputComponent->BindAxis("MoveForward", this, &AUE_World_Camera::MoveForward);

	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveRight", EKeys::A, 1.0f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveRight", EKeys::D, -1.0f));
	PlayerInputComponent->BindAxis("MoveRight", this, &AUE_World_Camera::MoveRight);*/


	//滚轮操作	
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("ScrollWheelUp", EKeys::MouseWheelAxis, 1.0f));
	PlayerInputComponent->BindAxis("ScrollWheelUp", this, &AUE_World_Camera::OnScrollWheelUpPress);

	//鼠标右键	
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MouseRightDrag", EKeys::RightMouseButton, 1.0f));
	PlayerInputComponent->BindAxis("MouseRightDrag", this, &AUE_World_Camera::OnMouseRightDrag);

	//键盘leftShift键	
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("KeyLeftShift", EKeys::LeftShift));
	PlayerInputComponent->BindAction("KeyLeftShift", IE_Pressed, this, &AUE_World_Camera::OnKeyLeftShiftPressed);
	PlayerInputComponent->BindAction("KeyLeftShift", IE_Released, this, &AUE_World_Camera::OnKeyLeftShiftReleased);

	//鼠标位置（X,Y方向）	
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("OnTurnRotate", EKeys::MouseX, 1.0f));
	PlayerInputComponent->BindAxis("OnTurnRotate", this, &AUE_World_Camera::OnTurnRotate);
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("LookAtRotate", EKeys::MouseY, 1.0f));
	PlayerInputComponent->BindAxis("LookAtRotate", this, &AUE_World_Camera::OnLookAtRotate);

}

// 输入函数
void AUE_World_Camera::MoveForward(float AxisValue)
{
	if (FMath::Abs(AxisValue) > KINDA_SMALL_NUMBER)
	{
		MoveDirection = FVector::ZeroVector;
		GetWorld()->GetFirstPlayerController()->GetMousePosition(CursorPos.X, CursorPos.Y);
		UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), CursorPos, WorldPos, MoveDirection);
		int32 moveStep = WorldPos.Z*MoveStepFactor*-1;
		MovementInput.X = FMath::Clamp<float>(AxisValue*moveStep, -1.0f*moveStep, 1.0f*moveStep);

		MovementInput = MovementInput.GetSafeNormal();
		FVector newLocation = GetActorLocation();
		newLocation += GetActorForwardVector()*MovementInput.X;
		SetActorLocation(newLocation);
	}
}

void AUE_World_Camera::MoveRight(float AxisValue)
{
	if (FMath::Abs(AxisValue) > KINDA_SMALL_NUMBER)
	{
		MoveDirection = FVector::ZeroVector;
		GetWorld()->GetFirstPlayerController()->GetMousePosition(CursorPos.X, CursorPos.Y);
		UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), CursorPos, WorldPos, MoveDirection);
		int32 moveStep = WorldPos.Z*MoveStepFactor*-1;

		MovementInput.Y = FMath::Clamp<float>(AxisValue*moveStep, -1.0f*moveStep, 1.0f*moveStep);

		MovementInput = MovementInput.GetSafeNormal();
		FVector newLocation = GetActorLocation();
		newLocation += GetActorRightVector()*MovementInput.Y;
		SetActorLocation(newLocation);
	}
}





//键盘shift左键的按下操作响应函数
void AUE_World_Camera::OnKeyLeftShiftPressed()
{
	IsBindShiftKey = true;
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, "key left shift pressed");
}

//键盘shift左键的抬起操作响应函数
void AUE_World_Camera::OnKeyLeftShiftReleased()
{
	IsBindShiftKey = false;
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, "key left shift released");
}


//滚动滑轮的事件响应函数
//用于操纵当前玩家的相机视野
//蒯希，20200410
void AUE_World_Camera::OnScrollWheelUpPress(float axisValue)
{
	MoveDirection = FVector::ZeroVector;
	if (FMath::Abs(axisValue) > KINDA_SMALL_NUMBER)
	{
		GetWorld()->GetFirstPlayerController()->GetMousePosition(CursorPos.X, CursorPos.Y);
		UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), CursorPos, WorldPos, MoveDirection);

		//根据当前控制器的实际高度，确定相机移动的实际步长(ScrollWheelSpeed)，原始移动步长(axisValue)为“1”
	    //目前逻辑为实际高度的10%作为步长，以放大视角操作为例，每次递进现有高度的10%，相机更新后的位置为原来高度的90%
	    //（蒯希，20191225）

		//默认滚轮放大，根据距离球面的距离，单次缩放距离逐渐缩小
		float stepRadio = 0.05;

		/*if (axisValue < 0)
			stepRadio = 1.05;*/
		
		float cameraHeight = FVector::Dist(WorldPos, SphereOrigin) - MaxSphereR;
		ScrollWheelSpeed = cameraHeight * stepRadio;
		OurCamera->AddWorldOffset(MoveDirection*ScrollWheelSpeed*axisValue);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::SanitizeFloat(cameraHeight));
	}
	
}

//鼠标右键的拖拽事件响应函数
//只是做逻辑判断，设置当前的操作标识，具体操作在CalcCameraOnTurn函数中完成
//蒯希20191225
void AUE_World_Camera::OnMouseRightDrag(float axisValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::SanitizeFloat(axisValue));
	if (FMath::Abs(axisValue) < KINDA_SMALL_NUMBER)
	{
		CurrentCursorPos = PreviousCursorPos = FVector2D::ZeroVector;
		IsRotateCameraState = false;
		IsMoveCameraState = false;
	}
	else
	{
		//按下左shift键，绕鼠标点旋转		
		if (IsBindShiftKey)
		{
			//拖拽状态			
			IsMoveCameraState = false;
			IsRotateCameraState = true;
		}
		//没有按下左Shift键时候，开始拖拽		
		else
		{
			IsRotateCameraState = false;
			IsMoveCameraState = true;
		}
	}
}




//具体相机平移操作逻辑的实现函数
//蒯希20191225
void AUE_World_Camera::CalcCameraMoveDragDirection()
{
	if (FMath::Abs(FVector2D::Distance(PreviousCursorPos, CurrentCursorPos)) < KINDA_SMALL_NUMBER)
	{
		GetWorld()->GetFirstPlayerController()->GetMousePosition(PreviousCursorPos.X, PreviousCursorPos.Y);
	}
	else
	{
		//1.获取相机当前在ue坐标系中的位置，并计算其在经纬度椭球上的坐标，及高度
		FVector currentCameraLocation = GetActorLocation();
		FVector currentCameraLocationInGlobe = this->sccts.TileCoordinateSystem.FromUE_CoordinateSystem(currentCameraLocation);
		//2.根据当前相机在经纬度椭球中的高度，计算单个像素对应的经纬度长度
		float degreePerPixel = this->sccts.GetDegreePerPixelInScreen();

		//3.获取当前鼠标位置，与之前记录的鼠标位置做差，得到在屏幕上的鼠标位移
		GetWorld()->GetFirstPlayerController()->GetMousePosition(CurrentCursorPos.X, CurrentCursorPos.Y);
		FVector2D MoveOffset = CurrentCursorPos - PreviousCursorPos;

		if(MoveOffset.X >10)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::SanitizeFloat(MoveOffset.X));
		
		PreviousCursorPos = CurrentCursorPos;

		//4.计算屏幕上的鼠标位移对应的经纬度位移
		FVector MoveOffsetInGlobe = FVector(MoveOffset.X*degreePerPixel, MoveOffset.Y*degreePerPixel,0);

		//5.计算最终的鼠标经纬度位置，并根据该位置反算UE中的坐标，将相机平移到该位置
		currentCameraLocationInGlobe = currentCameraLocationInGlobe.operator+(MoveOffsetInGlobe);
		FVector nextCameraLocation = this->sccts.TileCoordinateSystem.ToUE_CoordinateSystem(currentCameraLocationInGlobe);
		SetActorLocation(nextCameraLocation);

		//6.根据相机新的位置，计算相机位置到ue椭球原点的方向向量，通过该向量设置相机的偏转角度
		FVector nextCameraShootToOriginVector =  SphereOrigin - nextCameraLocation;
		OurCamera->RelativeRotation = nextCameraShootToOriginVector.Rotation();

		//根据实际高度，调整平移量
		//初步设置每次平移单位为高度值的0.01倍（经验值）
		//后续完善需要将该值设置为一个可以供用户修改的参数
		//MoveDirection = FVector::ZeroVector;
		//GetWorld()->GetFirstPlayerController()->GetMousePosition(CursorPos.X, CursorPos.Y);
		//UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), CursorPos, WorldPos, MoveDirection);

		//
		/////*if (axisValue < 0)
		////	stepRadio = 1.05;*/

		//float cameraHeight = FVector::Dist(WorldPos, SphereOrigin) - MaxSphereR;	

		//int32 moveStep = cameraHeight *MoveStepFactor;

		//OurCamera->AddLocalOffset(FVector(0, -MoveOffset.X*moveStep, MoveOffset.Y*moveStep));
	}
}


//默认的鼠标右键调整视角逻辑，根据mouseX的值,沿Z轴旋转，即偏航角的变化
void AUE_World_Camera::OnTurnRotate(float axisValue)
{
	if (!IsRotateCameraState) return;
	if (IsRotateCameraState&&FMath::Abs(axisValue) > KINDA_SMALL_NUMBER)
	{
		FRotator NewRotationYaw = GetActorRotation();
		NewRotationYaw.Yaw += axisValue;
		SetActorRotation(NewRotationYaw);
	}
}

//默认的鼠标右键调整视角逻辑，根据mouseY的值，沿Y轴旋转，即俯仰角的变化
//目前设置俯仰角的变化范围为-90 到-15，即垂直往下看到斜视地面15度的角度来看的范围，后续根据实际需要再调整
//蒯希20191225
void AUE_World_Camera::OnLookAtRotate(float axisValue)
{
	if (!IsRotateCameraState) return;
	if (IsRotateCameraState && FMath::Abs(axisValue) > KINDA_SMALL_NUMBER)
	{
		FRotator NewRotationPitch = OurCameraSpringArm->GetComponentRotation();
		NewRotationPitch.Pitch = FMath::Clamp(NewRotationPitch.Pitch + axisValue, -90.0f, -15.0f);
		OurCameraSpringArm->SetWorldRotation(NewRotationPitch);
	}
}

