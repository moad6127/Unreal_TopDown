# TopDown게임 

언리얼 엔진 5 를 이용해서 뱀파이어 서바이벌류 TopDown게임을 만들기

![TopDownGame](https://github.com/moad6127/Unreal_TopDown/assets/101626318/00158843-a210-463a-acf4-6a6f94ba6b91)


# *Title*

## *Title 화면*


>게임의 타이틀 화면으로 게임을 시작하는 버튼과 능력치를 강화할수 있는 버튼이 존재해 버튼을 누르면 해당 맵으로 이동하도록 만들었다.

- [헤더파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Public/HUD/TitleWidget.h)
- [CPP파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Private/HUD/TitleWidget.cpp)

![TopDownGame_TItle](https://github.com/moad6127/Unreal_TopDown/assets/101626318/8610d987-0999-4be5-b542-b9aea1bdbaad)


<details><summary> Title 클래스의 함수와 기능들</summary>
<p>
  
![TopDownGame_Title_h](https://github.com/moad6127/Unreal_TopDown/assets/101626318/b5974b05-7b8a-4b2d-8011-6c94c12d083a)
![TopDownGame_Title_cpp](https://github.com/moad6127/Unreal_TopDown/assets/101626318/51974790-59dd-4ad3-9a9d-9fa08ccde0e0)

> 단순히 버튼들을 바인딩한후 바인딩에 필요한 함수들을 구현해서 버튼을 클릭하면 해당 맵으로 이동하거나 종료 하도록 설정 하였다.

----------------------------------------------------------------------------------------------------
</p>
</details>

<details><summary> Title 맵의 Controller</summary>
<p>
  
![TopDownGame_TitleController](https://github.com/moad6127/Unreal_TopDown/assets/101626318/1fd9e498-08bf-4139-9565-eb256d910657)
![TopDownGame_TitleController_cpp](https://github.com/moad6127/Unreal_TopDown/assets/101626318/69f77317-41b8-40a8-96a1-5f0d11767a63)

> 맵으로 이동했을때 Controller의 BeginPlay를 통해서 Title의 Widget이 나타나도록 만들기 위해서 만들어진 컨트롤러로 단순히 Widget을 생성하고 화면에 띄우는 역할을 한다

----------------------------------------------------------------------------------------------------
</p>
</details>


## *강화 화면*

> 플레이해서 얻은 재화를 사용해서 캐릭터의 능력치들을 올릴수 있도록 만들었다.

- [헤더파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Public/HUD/Upgrade.h)
- [CPP파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Private/HUD/Upgrade.cpp)


![TopDownGame_Upgrade](https://github.com/moad6127/Unreal_TopDown/assets/101626318/d8f364fc-e569-4a74-8a3a-65b27b6c9ea6)

<details><summary> Upgrade 클래스의 대표 함수와 기능들</summary>
<p>

![TopDownGame_Upgrade_NativeConstruct](https://github.com/moad6127/Unreal_TopDown/assets/101626318/98be4bad-d658-4f11-b7f4-64ff69fe2cc9)

> SaveGame클래스를 활용하기 위해서 NativeConstruct함수에 필요한 정보들을 Load한후 각각의 Widget들의 정보를 업데이트 한다.

![TopDownGame_Upgrade_DamageBox_h](https://github.com/moad6127/Unreal_TopDown/assets/101626318/40f6f64a-37d7-4658-aac7-65704f79ea37)
![TopDownGame_Upgarde_DamageBox](https://github.com/moad6127/Unreal_TopDown/assets/101626318/7292bbdf-f816-4545-82c6-20a0584dc363)

> DamageUpgardeBox에 필요한 변수들과 함수들을 나타낸 것으로 버튼을 누르면 게임에서 얻은 재화가 강화에 필요한 재화보다 크거나 같을경우 능력치를 증가 시킨다.

![TopDownGame_Upgrade_saveNCanButton](https://github.com/moad6127/Unreal_TopDown/assets/101626318/479e6f2a-a8cb-42d7-96ad-d866f39e6a85)
> 저장버튼을 누르는 경우에만 Save를 하도록 설정하기
  
----------------------------------------------------------------------------------------------------
</p>
</details>


<details><summary> Title 맵의 Controller</summary>
<p>
  
![TopDownGame_UpgradeController_h](https://github.com/moad6127/Unreal_TopDown/assets/101626318/729db67e-a3dd-4b18-b013-93b23d318f50)
![TopDownGame_UpgradeController_cpp](https://github.com/moad6127/Unreal_TopDown/assets/101626318/4bf41dc3-4654-40d2-8a85-c66c44da7d6a)


> 맵으로 이동했을때 Controller의 BeginPlay를 통해서 Upgrade의 Widget이 나타나도록 만들기 위해서 만들어진 컨트롤러로 단순히 Widget을 생성하고 화면에 띄우는 역할을 한다

----------------------------------------------------------------------------------------------------
</p>
</details>


# *Character*

> 플레이어가 조종하는 Character로 EnhancedInput기능을 사용하며 ActorComponent를 활용해 캐릭터의 체력및 경험치를 조절하고 Enemy를 Spawn하는 역할까지 한다.

- [헤더파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Public/Character/TopDownCharacter.h)
- [CPP파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Private/Character/TopDownCharacter.cpp)

![TopDownGame_Character](https://github.com/moad6127/Unreal_TopDown/assets/101626318/cdd46026-28ca-4c1f-81ed-e9489f231475)


### *이동*


![TopDownGame_Character_Input](https://github.com/moad6127/Unreal_TopDown/assets/101626318/1b2077f7-dd64-4ff7-bab2-b0b442986a27)
![TopDownGame_Character_Move_Context](https://github.com/moad6127/Unreal_TopDown/assets/101626318/8c3f2eab-b2bf-4b51-9d71-2904a47a1f9f)

> EnhancedInput을 사용하기 위해서 InputAction과 InputContext를 만든후 Character에 변수로 추가해준다음 블루프린트로 설정해준 모습이다.

![TopDownGame_Character_PlayerInputComponent](https://github.com/moad6127/Unreal_TopDown/assets/101626318/6e5e8a55-d266-4e62-8c40-ed86d93aa588)

> SetupPlayerInputComponent 함수에서 EnhancedInput으로 Action을 바인딩해 필요한 함수와 연결한다.

![TopDownGame_Character_MoveFunc](https://github.com/moad6127/Unreal_TopDown/assets/101626318/6b0d2645-40af-4c45-8c9a-8fa9cad99e65)

> Character의 Move함수로 WASD로 움직이며 각각의 움직임이 발동되면 해당 함수를 불러와서 캐릭터를 이동 시킨다.


------------------------------------------------------------------------

### *공격*

> Character의 공격은 **단순한 발사체** 를 구현해서 발사하는 형식으로 만들어져 있다.


<details><summary> 발사체 </summary>
<p>
  
#### *발사체*

플레이어가 공격을 할때 사용하는 발사체로 단순히 BoxComponent에 Enemy가 Overlap되면 데미지를 주고 사라지게 만들어져 있다.

- [헤더파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Public/Attack/Projectile.h)
- [CPP파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Private/Attack/Projectile.cpp)

  
![TopDownGame_Attack_Projectile](https://github.com/moad6127/Unreal_TopDown/assets/101626318/4a2b619f-d555-4f48-9f73-ca83c131c294)

![TopDownGame_Attack_Projectile_CollisionOverlap](https://github.com/moad6127/Unreal_TopDown/assets/101626318/eb2375b9-6ce4-47ba-8cd3-7f839a3a2bfa)

> BoxComponent에 Overlap되는 대상이 Enemy의 태그를 가지고 있는경우 ApplyDamage를 통해서 데미지를 가해지도록 만들었다.

----------------------------------------------------------------------------------------------------
</p>
</details>

![TopDownGame_Attack_Func](https://github.com/moad6127/Unreal_TopDown/assets/101626318/45fbe5d5-b8fb-45ab-b979-4ad2cef1e4f9)

>Character클래스의 Attack함수이다. 타이머를 작동시키고 공격할 대상을 지정한다음 발사체를 구현해서 발사하도록 만들어져 있다.

![TopDownGame_Attack_Timer](https://github.com/moad6127/Unreal_TopDown/assets/101626318/4bfd079b-3ae0-4acc-a507-1c2af42ec53c)

> 공격 속도를 정하는 타이머로 타이머가 작동중일때는 공격하지 않도록 만들어져 있으며 타이머가 끝나면 다시 Attack함수를 호출한다
>  **Upgarde** 창에서 공격속도를 증가시키도록 할수 있다.

![TopDownGame_Attack_SetTarget](https://github.com/moad6127/Unreal_TopDown/assets/101626318/9ce6305c-d42f-4706-83a7-80f1f3fc79af)

> 현재 플레이어에게서 가장 가까운 Enemy를 탐색해서 공격할 대상을 지정하는 함수이다

![TopDownGame_Attack_SpawnProjectile](https://github.com/moad6127/Unreal_TopDown/assets/101626318/43907c8b-24ad-4440-85ed-c480c93f41e2)

> 탐색된 대상을 향해 발사체를 발사하도록 하며 공격할 대상이 존재하지 않을경우 Character의 ForwardVector방향으로 발사체를 발사하도록 만들어져 있다.


### *LevelUp*

![TopDownGame_LevelUpHUD](https://github.com/moad6127/Unreal_TopDown/assets/101626318/0a9b1b84-b5c2-492a-99af-3eea43b6c78c)

플레이어가 Enemy를 제거하였을때 나오는 경험치아이템을 먹고 최대 경험치에 도달하였을때 발생되도록 만든 이벤트로 플레이어의 능력치중 하나를 이번 게임동안 올릴수 있게 만들었다.


![TopDownGame_LevelUp_GetExP](https://github.com/moad6127/Unreal_TopDown/assets/101626318/c4f40af7-1def-4eaa-9fa7-9d287da764a4)

> 플레이어가 경험치 아이템을 얻었을때 만약 Max에 도달하였을경우 LevelUp함수를 호출하도록 설정했다.

![TopDownGame_LevelUp_Func](https://github.com/moad6127/Unreal_TopDown/assets/101626318/feb9564a-29f6-4b3c-bcb7-b39723566e33)

> Character클래스의 LevelUp함수로 이전 Max경험치에 1.5배를 해서 현재레벨의 Max를 결정한후 Controller의 LevelUp함수를 호출하도록 만들었다.

![TopDownGame_LevelUp_ControllerLevelUpFunc](https://github.com/moad6127/Unreal_TopDown/assets/101626318/e5fff50e-0440-4b0c-a7db-d829f0a092c9)

> Controller의 LevelUp함수로 설정된 LevelUpWidget을 만든후 랜덤하게 뽑힌 3개의 능력치를 화면에 보여주도록 만들었으며 레벨업중에는 게임이 일시정지되도록 설정했다.

![TopDownGame_LevelUP_ControllerRand](https://github.com/moad6127/Unreal_TopDown/assets/101626318/0216524c-9c56-4c46-9cc8-0f7ccf63913f)

> 3가지의 랜덤한 능력치를 선택하게 하는 함수로 RandRange를 사용해 하나를 고르며 중복된게 없을경우 Array에 추가하도록 만들었다.


<details><summary> LevelUpWidget </summary>
<p>

- [헤더파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Public/HUD/LevelUpWidget.h)
- [CPP파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Private/HUD/LevelUpWidget.cpp)

레벨업 이벤트가 발생할때 화면에 보여지는 Widget으로 단순한 WrapBox으로 이루어져 있으며 WrapBox에 SubWidget을 넣어서 화면을 구성하도록 만들었다.

  
 ![TopDownGame_LevelUp_LevelUpWidget_h](https://github.com/moad6127/Unreal_TopDown/assets/101626318/b26df3e1-c124-4c94-8bea-8cf2b18891a4)

 > SubWidgetClass와 WrapBox로 이루어져 있다.
> 
![TopDownGame_LevelUp_LevelUpWidget_cpp](https://github.com/moad6127/Unreal_TopDown/assets/101626318/5108eb99-d021-407f-9207-dd3b90665dd0)

> SubWidget을 Create한다음 필요한 정보들을 넘긴후 AddChild를 사용해 화면에 나타내도록 만들었다.


-----------------------------------------------------------------------------------------------------------------------------------------
</p>
</details>


<details><summary> LevelUpSubWidget </summary>
<p>

- [헤더파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Public/HUD/LevelUpSubSlotWidget.h)
- [CPP파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Private/HUD/LevelUpSubSlotWidget.cpp)

LevelUpWidget의 WrapBox에 Child로 구성되는 SubWidget으로 LevelUpWidget에서 넘어온 정보들을 활용해서 TextBox를 설정하도록 만들었다.

![TopDownGame_LevelUpSubWidget_NativeConstruct](https://github.com/moad6127/Unreal_TopDown/assets/101626318/d8671aa7-db5c-47b4-a9c5-6b601eb5083d)

> NativeConstruct함수로 LevelUpWidget에서 넘어온 CharacterState를 TextBox로 표시하도록 한다.

![TopDownGame_LevelUpSubWidget_ButtonClick](https://github.com/moad6127/Unreal_TopDown/assets/101626318/2b9aade4-5819-476e-82db-be701ae78eb0)

>LevelUpButton을 클릭했을때 나오는 이벤트로 해당 CharacterState의 Level을 올리고 LevelUpWidget을 제거한후 다시 게임을 이어나가도록 만들었다.


-----------------------------------------------------------------------------------------------------------------------------------------
</p>
</details>

### *GameResult*

![TopDownGame_GameResult](https://github.com/moad6127/Unreal_TopDown/assets/101626318/3b3312f1-c0d4-4dc4-bc55-f7b46e5d0728)

플레이어가 Enemy에게 데미지를 입어 체력이 0이 되면 나오는 결과화면으로 플레이중 획득한 Gold를 저장하고 타이틀 화면으로 돌아가도록 만들었다.

![TopDownGame_GameResult_CharacterTakeDamage](https://github.com/moad6127/Unreal_TopDown/assets/101626318/8563ab15-b04b-4a2b-88a9-28a44175e7f7)

> 플레이어가 Enemy에게 Damage를 받았을때 호출되는 함수로 체력이 0이 되면 Die함수가 호출되도록 만들었다.

![TopDownGame_GameResult_Die](https://github.com/moad6127/Unreal_TopDown/assets/101626318/6b9929a1-018b-4ecf-b56a-fa1647c5c368)

> Charater가 죽었을경우 호출되는 함수로 단순히 Controller에서 결과화면을 만들어내는 함수를 호출하도록 만든 함수이다.

![TopDownGame_GameResult_ControllerFunc](https://github.com/moad6127/Unreal_TopDown/assets/101626318/1647e7ce-6a73-4832-94fb-06133b2a1f7d)

> Controller에 변수로 저장된 GameResultWidget을 생성한후 화면에 표시하고 게임을 중단시키는 함수이다.


<details><summary> GameResultWidget </summary>
<p>

- [헤더파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Public/HUD/GameResultMenu.h)
- [CPP파일 주소](https://github.com/moad6127/Unreal_TopDown/blob/master/TopDown/Source/TopDown/Private/HUD/GameResultMenu.cpp)

GameResultWidget클래스로 단순한 버튼과 텍스트로 이루어져 있으며 버튼을 누르면 Title로 돌아가도록 만들었다.

![TopDownGame_GameResult_h](https://github.com/moad6127/Unreal_TopDown/assets/101626318/919629ad-f52a-4faa-bb76-51aea867b490)
![TopDownGame_GameResult_cpp](https://github.com/moad6127/Unreal_TopDown/assets/101626318/748c9692-ee59-4149-95a9-fcd408eeacbf)

> NativeConstruct함수에서 버튼의 클릭에 대한 이벤트를 처리한후 플레이중 획득한 Gold를 표시하고 Save하도록 만들어져 있다.



-----------------------------------------------------------------------------------------------------------------------------------------
</p>
</details>



# *Enemy*


# *Item*



