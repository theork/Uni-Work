
print("*********************************************************")
print("*       Welcome to Generic Magicy Text Adventure        *")
print("*********************************************************")

location = 'Start'
inventory = []
questStart = False
questComplete = False
playerType = 'NA'

#defining constants
DESC = 'desc'
NORTH = 'north'
SOUTH = 'south'
EAST = 'east'
WEST = 'west'
GROUND = 'ground'
GROUNDDESC = 'grounddesc'
SHORTDESC = 'shortdesc'
LONGDESC = 'longdesc'
TAKEABLE = 'takeable'
DESCWORDS = 'descwords'
NPCS = 'npc'
DIALOGUE1 = 'dialouge1'
DIALOGUE2 = 'dialouge2'
DIALOGUE3 = 'dialouge3'


worldRooms = {
    'Start': {
        DESC: """You have arrived in the starting area, there is a wide paved path that leads
south and an overgrown dirt track leading east that you see forks into two.""",
        NORTH: 'Caves',
        EAST: 'Forest',
        SOUTH: 'City Centre',
        GROUND:[],
        NPCS: []},
    'City Centre':{
        DESC: """You walk into the city centre. It is quiet here, few people walk past in a
hurry without making eye contact. There is a large golden statue of the king in the centre.""",
        NORTH: 'Start',
        EAST: 'Market',
        SOUTH: 'Castle',
        WEST: 'Temple',
        GROUND: ['King Statue'],
        NPCS: []},
    'Market': {
        DESC: """The market is much busier with people shouting their wares and the sound of
animals fill the air. """,
        WEST: 'City Centre',
        GROUND: ['Apple'],
        NPCS: ['Merchant']},
    'Blacksmith': {
        DESC: """The blacksmith shop is very hot, front and the sound of metal hitting
metal echos from the back room.""",
        EAST: 'Castle',
        GROUND: ['Sword'],
        NPCS: ['Smith']},
    'Staves':{
        DESC: """The staves shop is in a very small but tall building with a very old bearded
gentleman sat at the counter.""",
        NORTH: 'Castle',
        GROUND:['Staff'],
        NPCS: ['Mage']},
    'Castle': {
        DESC: """The castle gives the town a great stone backdrop that rises tall out of the
ground. There are many guards wearing red cloth over heavy armour.""",
        NORTH: 'City Centre',
        WEST: 'Blacksmith',
        SOUTH: 'Staves',
        GROUND:['Gold'],
        NPCS: ['King']},
    'Temple': {
        DESC: """The temple is set back from the main town down a small alley but is very grand
with golden coloured statues sitting guarding the entrance. There is a hushed
tone here and very few people are around.""",
        EAST: 'City Centre',
        GROUND: ['Alter'],
        NPCS: ['Monk']},
    'Caves': {
        DESC: """The caves are a dark and damp series of stone tunnels. It will be easy to get
lost here.""",
        WEST: 'Start',
        EAST: 'Prison',
        GROUND: ['Lantern'],
        NPCS: []},
    'Forest': {
        DESC: """The forest path leads down the hill into a large valley. You can just about make
out the other side of the forest on the other side of the valley, but it could
take many hours to traverse the dense plant life.""",
        WEST: 'Start',
        EAST: 'Prison',
        GROUND:[],
        NPCS: []},
    'Prison': {
        DESC: """The prison tower rises high almost touching the clouds on a stark, barren hill.
A large, ugly guard stands expressionless infront on the only entrance.""",
        NORTH: 'Caves',
        SOUTH: 'Forest',
        GROUND: ['Key', 'Rock'],
        NPCS: ['Guard', 'Princess']}
    }

worldItems = {
    'King Statue': {
        GROUNDDESC: 'The lavish golden statue of the king glints in the sun',
        SHORTDESC: 'a large statue of the king',
        LONGDESC: """On closer inspection you see that the statue is made of a cheap metal and
is only painted to look gold""",
        TAKEABLE: False,
        DESCWORDS: ['statue', 'king']},
    'Apple': {
        GROUNDDESC: 'A merchant is selling apples',
        SHORTDESC: 'A juicy red apple',
        LONGDESC: 'Juicy round apples are being sold by a merchant. Good for keeping doctors away.',
        TAKEABLE: False,
        DESCWORDS: ['apple', 'apples']},
    'Sword': {
        GROUNDDESC: 'Shiny swords hang on the walls',
        SHORTDESC: 'Sharp sword',
        LONGDESC: 'The blacksmith sells swords that are very good at cutting things.',
        TAKEABLE: False,
        DESCWORDS: ['sword', 'swords']},
    'Staff': {
        GROUNDDESC: 'Long wooden sticks are being sold here',
        SHORTDESC: 'A blunt quarterstaff',
        LONGDESC: 'Long wooden quaterstaff that is very good at hitting things from medium range',
        TAKEABLE: False,
        DESCWORDS: ['staff', 'staves', 'stave', 'staffs', 'quaterstaff']},
    'Alter': {
        GROUNDDESC: 'An alter filled with ornaments sits on the ground',
        SHORTDESC: 'An alter to pray',
        LONGDESC: 'The alter has a red cloth and many different ornaments on it',
        TAKEABLE: False,
        DESCWORDS: ['alter', 'pray','prayer']},
    'Lantern': {
        GROUNDDESC: 'A leftover lantern still with fuel lays on a stone shelf.',
        SHORTDESC: 'a lantern',
        LONGDESC: 'An old candle lantern. Used for finding your way through the caves.',
        TAKEABLE: True,
        DESCWORDS: ['light', 'lantern', 'lanterns']},
    'Key': {
        GROUNDDESC: 'A bronze key hides under a stone',
        SHORTDESC: 'A key',
        LONGDESC: 'This key looks like it could be used to open a door',
        TAKEABLE: False,
        DESCWORDS: ['key', 'keys']},
    'Gold': {
        GROUNDDESC: 'A big plile of gold',
        SHORTDESC: 'GOLD',
        LONGDESC: 'The king seems to have hoarded a lot of gold',
        TAKEABLE: False,
        DESCWORDS: ['gold', 'money'],},
    'Rock': {
        GROUNDDESC: 'A strange shaped rock',
        SHORTDESC: 'A stone',
        LONGDESC: 'An oddly shaped stone, looks good for hiding things under',
        TAKEABLE: True,
        DESCWORDS: ['stone', 'rock']}
    
    }



npcs = {
    'Smith': {
        DESC: 'A big blacksmith is working at the back of the shop.',
        DIALOGUE1: '"Welcome to my sword shop, your standard sword is 100 gold pieces."',
        DIALOGUE2: '"The king sent you? Take whatever sword takes your fancy."',
        DIALOGUE3: '"We do not deal with you kind in here! Go back to your wizzard\'s shop."'},
    'Mage': {
        DESC: 'A mage sits behind the counter reading a book.',
        DIALOGUE1: '"Hello! If you are in the market for a staff, it will be 70 gold."',
        DIALOGUE2: '"For your quest, you may choose any staff."',
        DIALOGUE3: '"Leave before you poke someone\'s eye out!"'},
    'Guard': {
        DESC: 'A large armoured guard stands infront of the entrance.',
        DIALOGUE1: '"You may not enter this prison!"'},
    'Merchant': {
        DESC: 'One merchant is selling fruit.',
        DIALOGUE1: '"Apples for sale, only 3 gold!"',
        DIALOGUE2: '"Please take an apple for your great quest."'},
    'Princess': {
        DESC: 'The princess sits on windowsill expectantly.',
        DIALOGUE1: '"Thank you for saving me! I will make sure you are rewarded greatly."'},
    'King': {
        DESC: 'A small man with a golden crown paces back and forth with small, quick strides.',
        DIALOGUE1: '''"Peasant, I need you for a quest! Save my daugter from the evil prince in the
neighbouring lands. I will make sure you are kitted out with a weapon
of your choice."''',
        DIALOGUE2: 'Take this gold as a reward.',
        DIALOGUE3: 'What are you waiting for?'},
    'Monk': {
        DESC: 'A monk is kneeling behind the alter.',
        DIALOGUE1: '"You have been blessed."'}

    }




def displayLocation(loc):
    #prints the room name
    print()
    print(loc)
    print('=' * len(loc))
    #prints description of the room
    print(worldRooms[loc][DESC])

    #tests to see if there is items on the ground
    if len(worldRooms[loc][GROUND]) > 0:
        #lists each item in the room
        for item in worldRooms[loc][GROUND]:
            print(worldItems[item][GROUNDDESC])

    #displays any npcs (if there are any)
    if len(worldRooms[loc][NPCS]) > 0:
        for i in worldRooms[loc][NPCS]:
            print(i)
            print(npcs[i][DESC])

    #displays the directions that the user can move
    for  direction in (NORTH, SOUTH, EAST, WEST):
        if direction in worldRooms[location]:
            print('%s: %s' % (direction.title(), worldRooms[location][direction]))


def moveDirection(direction):

    global location

    #tests if the input is valid
    if direction in worldRooms[location]:
        print('You move ' + direction)
        #updates location
        location = worldRooms[location][direction]
        displayLocation(location)
    else:
        print('Invalid direction')



#returns all the desc words in the worldItems dictionary
def getAllDescWords(itemList):
    #makes the list unique
    itemList = list(set(itemList))
    descWords = []
    for item in itemList:
        #adds words from worldItems to list
        descWords.extend(worldItems[item][DESCWORDS])
    return list(set(descWords))

#returns the first words in the DESCWORDS list
def getAllFirstDescWords(itemList):
    #makes list unique
    itemList = list(set(itemList))
    descWords = []
    #adds first entry of worldItems list to descWords
    for item in itemList:
        descWords.append(worldItems[item][DESCWORDS][0])
    return list(set(descWords))

#returns the first item name that matches passed description
def getFirstItemMatchingDesc(desc, itemList):
    #makes list unique
    itemList = list(set(itemList))
    for item in itemList:
        if desc in worldItems[item][DESCWORDS]:
            return item
    return None

#returns all the item names that matches passed description
def getAllItemsMatchingDesc(desc, itemList):
    #makes list unique
    itemList = list(set(itemList))
    matchingItems = []
    for item in itemList:
        #checks to see if description is in the dictionary and adds if true
        if desc in worldItems[item][DESCWORDS]:
            matchingItems.append(item)
    return matchingItems



def displayInventory():
    #if inventory is empty
    if len(inventory) == 0:
        print('You have nothing')
        return
    itemCount = {}
    for item in inventory:
        #adds a count to prevent dupicates
        if item in itemCount.keys():
            itemCount[item] += 1
        else:
            itemCount[item] = 1

    #outputs the inventory with counts if applicable
    print('\nInventory')
    print('=========')
    for item in set(inventory):
        if itemCount[item] > 1:
            print(' ' + item + ' ' + itemCount[item])
        else:
            print(' ' + item)


def takeItem(itemToTake):
    #finds item on the ground
    for item in getAllItemsMatchingDesc(itemToTake, worldRooms[location][GROUND]):
        if worldItems[item].get(TAKEABLE, True) == False:
            print('You are unable to take this')
            return
        #appropiate to quest
        if itemToTake in ('key', 'keys'):
            if 'Sword' not in inventory and 'Staff' not in inventory:
                print("""The guard catches you trying to get in. You try and fight back but you are
unable to fight without a good weapon""")
                exit()
            else:
                print("The guard catches you tring to get in but you defeat him with your weapon")
                #guard dies so removes him from the room
                worldRooms[location][NPCS].remove('Guard')
        print('You pick up ' + itemToTake)
        #removes item from ground and adds to inventory
        worldRooms[location][GROUND].remove(item)
        inventory.append(item)

        #allows the key to be taken under the rock
        if itemToTake in ('rock', 'stone'):
            worldItems['Key'][TAKEABLE] = True
        
        return
    print('That item is not on the ground')


def dropItem(itemToDrop):
    #gets all descriptions from items in inventory
    invDescWords = getAllDescWords(inventory)
    #checks if item is in the inventory
    if itemToDrop not in invDescWords:
        print('You do not have that in your inventory')
        return

    #verification that the user wants to drop
    print('Are you sure you want to drop your ' + itemToDrop + '? (Y/N)')
    response = input().upper()
    if response == 'Y':
        #gets the item name
        item = getFirstItemMatchingDesc(itemToDrop, inventory)
        print('You drop ' + worldItems[item][SHORTDESC])
        inventory.remove(item)
        #adds the item to the ground
        worldRooms[location][GROUND].append(item)
    else:
        print('Drop canceled')


def look(thing):
    #displays area description if input blank
    if thing == '':
        displayLocation(location)
        return

    #redisplays the exits of the area
    elif thing == 'exits':
        for direction in (NORTH, SOUTH, EAST, WEST):
            if direction in worldRooms[location]:
                print('%s: %s' % (direction.title(), worldRooms[location][direction]))
        return

    #displays only one exit
    elif thing in ('north', 'west', 'south', 'east', 'n', 'w', 's', 'e'):
        #startswith allows the input to have long and short forms condensed into the same statement
        #also checks if current room has a valid inputted direction
        if thing.startswith('n') and NORTH in worldRooms[location]:
            print(worldRooms[location][NORTH])
        elif thing.startswith('w') and WEST in worldRooms[location]:
            print(worldRooms[location][WEST])
        elif thing.startswith('s') and SOUTH in worldRooms[location]:
            print(worldRooms[location][SOUTH])
        elif thing.startswith('e') and EAST in worldRooms[location]:
            print(worldRooms[location][EAST])
        else:
            print('There is nothing in that direction')
        return

    #checks if the item is on the ground
    item = getFirstItemMatchingDesc(thing, worldRooms[location][GROUND])
    if item != None:
        print(worldItems[item][LONGDESC])
        return

    #checks if the item is in the player's inventory
    item = getFirstItemMatchingDesc(thing, inventory)
    if item != None:
        print(worldItems[item][LONGDESC])
        return

    #reaches this statement if input is invalid
    print('You do not see that nearby. Try look + item or direction')


def talk(npc):
    global questStart
    global playerType
    global questComplete
    
    #check if npc is in room
    if npc in worldRooms[location][NPCS]:
        print('You are talking with the ' + npc)
    else:
        print(npc + ' is not in this room')
        return

    #finds which dialouge to output if there is a choice and changes item properties to do with quest
    if npc == 'Smith':
        if playerType == 'Mage':
            print(npcs[npc][DIALOGUE3])
            return
        if questStart == True:
            print(npcs[npc][DIALOGUE2])
            playerType = 'Warrior'
            worldItems['Sword'][TAKEABLE] = True
            worldItems['Staff'][TAKEABLE] = False
            return
    elif npc == 'Mage':
        if playerType == 'Warrior':
            print(npcs[npc][DIALOGUE3])
            return
        if questStart == True:
            print(npcs[npc][DIALOGUE2])
            playerType = 'Mage'
            worldItems['Staff'][TAKEABLE] = True
            worldItems['Sword'][TAKEABLE] = False
            return
    elif npc == 'Merchant':
        if questStart == True:
            print(npcs[npc][DIALOGUE2])
            worldItems['Apple'][TAKEABLE] = True
            return
    elif npc == 'King':
        if questComplete == True:
            print(npcs[npc][DIALOGUE2])
            worldItems['Gold'][TAKEABLE] = True
            return
        elif questStart == True:
            print(npcs[npc][DIALOGUE3])            
            return
        questStart = True 
    elif npc == 'Princess':
        if 'Key' in inventory:
            questComplete = True
            if location == 'Prison':
                #moves princess from prison to castle
                worldRooms[location][NPCS].remove('Princess')
                worldRooms['Castle'][NPCS].append('Princess')
                
        else:
            print("You cannot reach the princess")
            return

    print(npcs[npc][DIALOGUE1])
    return


#displays the first location
displayLocation(location)
while True:
    #converts input to lowercase
    response = input("\n>>").lower()
    
    if response == 'quit':
        break

    elif response in ('north', 'west', 'south', 'east', 'n', 'w', 's', 'e'):
        #adds shortcuts
        if response == 'n':
            response = 'north'
        elif response == 'w':
            response = 'west'
        elif response == 's':
            response = 'south'
        elif response == 'e':
            response = 'east'
        moveDirection(response)
        
    elif response in ('look', 'l'):
        print("\tWhat is it you want to look at?")
        lookResponse = input("\t>>").lower()
        look(lookResponse)

    elif response in ('talk', 'speak', 't'):
        print("\tWho is it that you want to talk to?")
        talkResponse = input("\t>>").title()
        talk(talkResponse)
        
    elif response in ('drop', 'drop item', 'd'):
        print("\tWhat item do you want to drop?")
        dropResponse = input("\t>>").lower()
        dropItem(dropResponse)

    elif response in ('take', 'pickup', 'pick', 'p'):
        print("\tWhat item do you want to pickup?")
        takeResponse = input("\t>>").lower()
        takeItem(takeResponse)

    elif response in ('inventory', 'bag', 'i', 'inv'):
        displayInventory()    

    elif response in ('help', 'h'):
        print("""\nCommands

Exit: Type 'quit' to exit

Movement: 'north', 'south', 'east', 'west' or 'n', 's', 'e', 'w' to move around the map

Look: use the 'look' or 'l' command to look at objects and things.
-Can be used with blank input to re-display area information.
-Can be used with a direction to display area information in that direction.
-Can be used with an item to display detailed information about an item in
inventory or on ground.
-Can be given with 'exits' command to display description of all areas nearby.

Talking to NPCS: use the 'talk' or 't' command to talk to an NPC.
-Then give the character name of the character you want to talk to.

Inventory: use 'inventory' or 'i' to display your inventory.

Dropping items: use 'drop' or 'd' command to drop an item.
-The item can then be picked up later.

Taking items: use 'take', 'pick' or 'p' command to pickup an item.
-The item is then moved into your inventory.

""")

    else:
        print('Invalid input, type help to view commands')
        
        

