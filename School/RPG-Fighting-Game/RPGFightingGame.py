#importing required modules
import random

#opening file
file = open("monster.csv", "w")

#welcoming user
print("Welcome to Ginal Gantasy V — you'll be fighting Gepiroth!")

#initializing monster health and turn for csv file
turn=1

monsterhealth = [
    [40, 45, 47],
    [43, 48, 53],
    [50, 55, 60]
]

#randomly selecting monster health
row = random.randint(0, 2)
column = random.randint(0, 2)
monster_hp = monsterhealth[row][column]


#Class for commands
class Fight:
    def __init__(self):
        #player and monster hp, creating objects
        self.player_hp = 25
        self.monster_hp = monster_hp
        self.monster_max_hp = monster_hp
        
        #for capture
        self.captured = False
        
        #for befreind
        self.friendship = 0
    
    def monsterattack(self):
        #randomizing monster attack from 2 to 6
        damageM = random.randint(2,6)
        
        #removing health from player
        self.player_hp -= damageM
        
        #inform user
        print(f"Gephiroth attacks. He damages you by {damageM} HP points. You have {self.player_hp} HP points left")
        
        #end game if user is less than 0 hp
        if self.player_hp <= 0:
            print("You died")
      
    def attack(self):
        #choosing randomized damage for player attack
        damage = random.choice([4, 6, 6, 8, 10, 10])
        
        #remove health from monster
        self.monster_hp -= damage
        
        #inform user
        print(f"You damaged Gepiroth by {damage} HP")
        
        #end game if monster dies
        if self.monster_hp <= 0:
            print("You defeated Gepiroth")

    def heal(self):
        #choosing how much the heal the player by
        heal_amount = random.randint(3, 8)
        
        #keeping track of old HP 
        old_hp = self.player_hp
        
        #add healed HP points to user
        self.player_hp += heal_amount

        #Capping HP to 25 
        if self.player_hp > 25:
            self.player_hp = 25
        
        #amount healed 
        actual_healed = self.player_hp - old_hp
        
        #telling user they're at full health
        if actual_healed == 0:
            print("Youre at full HP already, nothing healed")
        else:
            print(f"You healed {actual_healed} HP points. Your current health: {self.player_hp} HP.")

    def capture(self):
        #making odds
        capture_odds = ((self.monster_max_hp - self.monster_hp) / self.monster_max_hp) * 100
        
        #roll
        roll = random.randint(0, 100)
        
        #inform user of odds
        print(f"You throw a poke ball. Chance of Success: {capture_odds}%")
        print(f"Your roll: {roll}")
        
        #successful roll
        if roll <= capture_odds:
            print("You caught Gepiroth")
            
            #end game by setting hp to 0 
            self.monster_hp = 0  
            self.captured = True
            
        #unsuccesful roll
        else:
            print("The capture failed! The monster broke free!")
            self.captured = False
     
    def befriend(self):
        
        #setting increase from 1 to 3 points
        increase = random.randint(1, 3)
        
        #add points to friendship
        self.friendship += increase

        print(f"You give the monster a bit of your backstory. Gepiroth's sympathy increases by {increase} points. Total friendship: {self.friendship}/10")

        #check if friendship is over 10
        if self.friendship >= 10:
            print("Talk no jitsu worked, you befriended the monster")
            #end fight
            self.monster_hp = 0  

#intialize class        
fight = Fight()

# Loop that runs the fight 
while fight.monster_hp > 0 and fight.player_hp > 0:
    
    try:
        #telling player what they can do 
        choice = int(input("Choose 1 to 4. 1 is attack, 2 is heal, 3 capture, 4 is befriend: "))

        # Matching number to choice and move. Also recording and putting in text file
        match choice:
            case 1:
                fight.attack()
                file.write(f"Turn {turn}: attacked\n")
            case 2:
                fight.heal()
                file.write(f"Turn {turn}: heal\n")
            case 3:
                fight.capture()
                file.write(f"Turn {turn}: capture\n")
            case 4:
                fight.befriend()
                file.write(f"Turn {turn}: befriend\n")
            

        #monster dealing damage
        if fight.monster_hp > 0:
            fight.monsterattack()
        
        #keeping track of turn for csv file
        turn +=1
            
    #identifying invalid choice instead of ending program
    except ValueError:
        print("Invalid choice, choose a number from 1–4 again.")

        
#write if monster or player won with if statements
if fight.monster_hp <= 0:
    file.write(f"Player won")
elif fight.player_hp <=0:
    file.write(f"Monster won")
            
#closing file
file.close()


    
            
