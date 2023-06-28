import random
print("Winning rules of the rock papar scissor game as follows:\n"
+"rock vs paper->paper wins\n"+"rock vs scissor->rock wins\n"+"scissor vs paper->scissor wins\n")
while True:
    print("enter choice\n 1 for rock \n 2 for paper \n 3 for scissor \n ")
    choice=int(input("user turn: "))
    while choice>3 or choice<1:
        choice=int(input("enter valid input:"))
    if choice==1:
        choice_name="rock"
    elif choice==2:
        choice_name="paper"
    else:
        choice_name="scissor"
    print("user choice is: " + choice_name)
    print("\n now its computer\'s turn.")
    comp_choice=random.randint(1,3)
    while comp_choice==choice:
        comp_choice=random.randint(1,3)
    if comp_choice==1:
        comp_choice_name="rock"
    elif comp_choice==2:
        comp_choice_name="paper"
    else:
        comp_choice_name="scissor"
    print("computer choice is: "+ comp_choice_name)
    print(choice_name + " vs " + comp_choice_name)
    if((choice==1 and comp_choice==2) or (choice==2 and comp_choice==1)):
        print("paper wins=>", end=" ")
        result="paper"
    elif((choice==1 and comp_choice==3) or (choice==3 and comp_choice==1)):
        print("rock wins=>", end=" ")
        result="rock"
    else:
        print("scissor wins=>", end=" ")
        result="scissor"
    if result==choice_name:
        print(" user wins")
    else:
        print(" computer wins")
    print("do you want to play again?(y/n)")
    ans=input()
    if ans=="n" or ans=="N":
        break
print("\n thanks for playing")
    