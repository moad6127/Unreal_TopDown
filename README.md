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




# *Enemy*


# *Item*



