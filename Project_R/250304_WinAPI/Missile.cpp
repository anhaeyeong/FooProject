#include "Missile.h"

void Missile::Init() {
	pos = { 0, 0 };
	isActived = false;
	moveSpeed = 3.0f;
	size = 10;
	angle = 90.0f;
}

void Missile::Release()
{
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}
}

void Missile::Update() {
	Move();
	if (isActived && IsOutofScreen()) {
		isActived = false;
	}
	UpdateCollisionRect();
}

void Missile::Render(HDC hdc) {
	if (image) {
		image->Render(hdc, pos.x, pos.y);
	}
	else {
		std::cerr << "." << std::endl;
	}
}

bool Missile::IsOutofScreen()
{
	float right = pos.x + size / 2;
	float left = pos.x - size / 2;
	float top = pos.y - size / 2;
	float bottom = pos.y + size / 2;

	if (right < 0 || left > WINSIZE_X
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}

void Missile::UpdateCollisionRect()
{
	rect = GetRectAtCenter(pos.x, pos.y, size, size);
}

void NormalMissile::Render(HDC hdc) {
	if (image) {
		image->Render(hdc, pos.x, pos.y);
	}
	else {
		std::cerr << "이미지가 로드되지 않았습니다." << std::endl;
	}
}


void NormalMissile::Move() {
	pos.y -= moveSpeed * angle * TimerManager::GetInstance()->GetDeltaTime() * 10;
}

void NormalMissile::Notice() {
	if (owner == MissileOwner::PLAYER) {
		moveSpeed = 3.0f;
		size = 10;
		angle = 90.0f;
	}
	else if (owner == MissileOwner::ENEMY) {
		moveSpeed = 3.0f;
		size = 10;
		angle = -90.0f;
	}

}

void NormalMissile::loadImage() {
	string imageKey = (owner == MissileOwner::PLAYER) ? "player_normal" : "enemy_normal";
	wstring imagePath = (owner == MissileOwner::PLAYER) ? L"Image/bullet.bmp" : L"Image/bullet.bmp";
	image = ImageManager::GetInstance()->AddImage(
		imageKey, imagePath.c_str(), 21, 21, 1, 1,
		true, RGB(255, 0, 255));

	if (!image) {
		std::cerr << "Failed to load image: " << std::string(imagePath.begin(), imagePath.end()) << std::endl;
	}
}
//SignMissile
void SignMissile::Render(HDC hdc) {
	if (image) {
		image->FrameRender(hdc, pos.x, pos.y, 0, currFrame);
	}
	else {
		RECT rc = GetRectAtCenter(pos.x, pos.y, size, size);
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
		std::cerr << "이미지가 로드되지 않았습니다." << std::endl;
	}
}

void SignMissile::Move() {
	float deltatime = TimerManager::GetInstance()->GetDeltaTime();
	pos.y -= moveSpeed * deltatime * 50;
	pos.x = initialPosX + 50 * sin(DEG_TO_RAD(pos.y));

	SignUpdate();
}

void SignMissile::Notice() {
	if (owner == MissileOwner::PLAYER) {
		isActived = true;
		moveSpeed = 50.0f;
		size = 10;
		initialPosX = pos.x;
		currFrame = 0;
		animElapsedTime = 0.0f;
	}
}

void SignMissile::loadImage() {
	string imageKey = (owner == MissileOwner::PLAYER) ? "player_civil_missile" : "enemy_civil_missile";
	wstring imagePath = (owner == MissileOwner::PLAYER) ? L"Image/civil.bmp" : L"Image/civil.bmp";
	image = ImageManager::GetInstance()->AddImage(
		imageKey, imagePath.c_str(), 23, 166, 1, 5,
		true, RGB(255, 255, 255));
	if (!image) {
		std::cerr << "Failed to load image: " << std::string(imagePath.begin(), imagePath.end()) << std::endl;
	}
}

void SignMissile::SignUpdate()
{
	animElapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (animElapsedTime >= 0.1f)
	{
		currFrame++;
		if (currFrame >= 5) {
			currFrame = 0;
		}
		animElapsedTime = 0.0f;
	}
	if (IsOutofScreen()) {
		isActived = false;
	}
	UpdateCollisionRect();
}

void LazerMissile::Render(HDC hdc) {
	if (image) {
		image->FrameRender(hdc, pos.x, pos.y - 630, animationFrame, 0);
	}
	else {
		std::cerr << "이미지가 로드되지 않았습니다." << std::endl;
	}
}

void LazerMissile::Move() {
	UpdateAnim();
	if (InputManager::isMoveLeft())
	{
		pos.x -= TimerManager::GetInstance()->GetDeltaTime() * 500;
	}

	if (InputManager::isMoveRight())
	{
		pos.x += TimerManager::GetInstance()->GetDeltaTime() * 500;
	}

	if (InputManager::isMoveUp())
	{
		pos.y -= TimerManager::GetInstance()->GetDeltaTime() * 500;
	}
	if (InputManager::isMoveDown())
	{
		pos.y += TimerManager::GetInstance()->GetDeltaTime() * 500;
	}

}

void LazerMissile::Notice() {
	if (owner == MissileOwner::PLAYER) {
		isActived = true;
		moveSpeed = 3.5f;
		size = 50;
	}
	else if (owner == MissileOwner::ENEMY) {
		isActived = true;
		moveSpeed = 3.5f;
		size = 50;
		angle = -90;
	}
}

void LazerMissile::loadImage() {
	std::string imageKey = (owner == MissileOwner::PLAYER) ? "player_Lazer_missile" : "enemy_Lazer_missile";
	std::wstring imagePath = (owner == MissileOwner::PLAYER) ? L"Image/LongLazer.bmp" : L"Image/LongLazer.bmp";
	image = ImageManager::GetInstance()->AddImage(
		imageKey, imagePath.c_str(), 345, 1259, 5, 1,
		true, RGB(255, 255, 255));
}

void LazerMissile::UpdateCollisionRect()
{
	rect = GetRectAtCenter(pos.x, pos.y - 630, size, size * 25);
}

void LazerMissile::UpdateAnim()
{
	elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (elapsedTime >= 0.1f)
	{
		animationFrame++;
		if (animationFrame >= 5)
		{
			animationFrame = 0;
			isActived = false;
		}

		elapsedTime = 0.0f;
	}
	/*remainTime -= TimerManager::GetInstance()->GetDeltaTime();
	if (remainTime <= 0.0f)
	{
		isActived = false;
		remainTime = 0.5f;
	}*/
}

void BossMissile::Render(HDC hdc)
{
	if (image) {
		image->Render(hdc, pos.x, pos.y);
	}
	else {
		std::cerr << "이미지가 로드되지 않았습니다." << std::endl;
	}
}

void BossMissile::Move()
{
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	int moveCount = 0;
	// 시간이 지날수록 속도 증가
	moveSpeed += (rand() % 10) * deltaTime;

	// 부메랑 효과를 위한 곡선 이동 (sin 함수 활용)
	float frequency = 3.0f; // 진동 빈도
	float amplitude = 50.0f; // 진폭 (좌우 움직임 범위)

	// x 좌표를 기준으로 sin 곡선을 적용하여 좌우 이동 추가
	pos.x += sin(pos.y * 0.05f) * amplitude * deltaTime;

	// y 방향 이동 (기본 이동)
	pos.y += moveSpeed * deltaTime * 10;

	// 일정 거리 도달하면 방향 반전 (왕복 운동 효과)
	if (pos.y > WINSIZE_Y || pos.y < 0)
	{
		moveSpeed = -moveSpeed; // 속도 반전하여 되돌아옴
		moveCount++; // 왕복 횟수 증가
	}
	isActived = false;
}







void BossMissile::Notice()
{
	if (owner == MissileOwner::PLAYER) {
		moveSpeed = 3.0f;
		size = 10;
		angle = 90.0f;
	}
	else if (owner == MissileOwner::ENEMY) {
		moveSpeed = 3.0f;
		size = 10;
		angle = -90.0f;
	}
}

void BossMissile::loadImage()
{
	string imageKey = (owner == MissileOwner::PLAYER) ? "player_normal" : "enemy_normal";
	wstring imagePath = (owner == MissileOwner::PLAYER) ? L"Image/bullet.bmp" : L"Image/bullet.bmp";
	image = ImageManager::GetInstance()->AddImage(
		imageKey, imagePath.c_str(), 21, 21, 1, 1,
		true, RGB(255, 0, 255));

	if (!image) {
		std::cerr << "Failed to load image: " << std::string(imagePath.begin(), imagePath.end()) << std::endl;
	}
}

void BossMissile::UpdateCollisionRect()
{
	rect = GetRectAtCenter(pos.x, pos.y, size, size);
}

void BossMissile::BossUpdateAnim()
{

}
