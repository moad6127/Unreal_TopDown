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



# *Enemy*


# *Item*



