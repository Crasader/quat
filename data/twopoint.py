#!/usr/bin/python
import csv, random, os, math

# The file containing words and their frequencies (separated by a space)
WORD_FILE = 'test'

# Check to make sure it exists
if not os.path.exists(WORD_FILE):
	print "Word file %s does not exist." % WORD_FILE



words = {}


"""If the map file, which has a cached list of words and their successors, does
not exist, we generate a CSV with that information."""
MAP_FILE = WORD_FILE + '.map'
if not os.path.exists(MAP_FILE):

	print "Map file does not exist for word list '%s'." % WORD_FILE
	
	# Open up the word file
	with open(WORD_FILE) as word_file:

		# Create a temporary array holding each word and its integer frequency
		word_list = []

		# Iterate over all the lines in the word file
		for line in word_file:
			# We strip the string to get the \n off
			parts = line.strip().split()

			# Adds a tuple of (word,frequency) to the list
			word_list.append((parts[0], int(parts[1])))


		# Iterate over all the words we added and find all the possible
		# successors for each word
		for word in word_list:

			# Array of branches off this word
			# Might as well calculate now
			poss = []


			# Look at every word in word_list and see if they differ by
			# 1 letter
			for w in word_list:


				diffs = 0

				# Count the number of differences between the two words
				for i in range(0,4):
					if not word[0][i] == w[0][i]:
						diffs += 1

				# If it's only one, add it to the list of successors
				if diffs == 1:
					poss.append(w[0])

			words[word[0]] = (poss,word[1])

	# Bake it all to a file
	with open(MAP_FILE, 'wb') as map_file:
		map_writer = csv.writer(map_file, delimiter='\t')
		for word in words:
			data = words[word]
			
			map_writer.writerow([word,data[1],','.join(data[0])])
else:
	print "Map exists for word file '%s'." % WORD_FILE

	# Restore the map from the file
	with open(MAP_FILE, 'rb') as map_file:
		map_reader = csv.reader(map_file, delimiter='\t')
		for row in map_reader:
			succ = row[2].split(',')
			if len(succ) == 1 and succ[0] == '':
				succ = []

			freq = int(row[1])


			words[row[0]] = (succ,freq)



print "Number of words: %d." % len(words)

def solve(start,finish):
	measures = {}
	for word in words:
		data = words[word]
		measures[word] = {
			'distance': -1,
			'predecessor': 'nil',
			'frequency': data[1]
		}

	queue = []
	queue.append(start)

	while len(queue) > 0:
		word = queue.pop(0)

		if word == finish:
			solution = []

			current = word
			solution.append(word)
			while current != start:
				solution.append(measures[current]['predecessor'])
				current = measures[current]['predecessor']
				
			solution.reverse()
			return solution

		for adjacent in words[word][0]:
			if adjacent == '':
				print words[word][0]
				exit()
			if measures[adjacent]['distance'] == -1:
				measures[adjacent]['distance'] = measures[word]['distance'] + 1
				measures[adjacent]['predecessor'] = word
				queue.append(adjacent)

	return []

# Get the 'easiness' of a word, which is a number that reflects how
# Easy it is to think of words that connect to it
def easiness(word):
	word = words[word]

	frequency = float(word[1])

	# These determine how forgiving the algorithm is to uncommon words
	steps = 4
	threshhold = 30000

	step_size = math.floor(float(threshhold) / float(steps))

	# Keep track of a moving value
	value = 0.0
	frequencies = [words[x][1] for x in word[0]]

	for i in range(steps):
		current_threshhold = threshhold - (step_size * i)
		value += len([f for f in frequencies if f > current_threshhold]) * (pow(10,-i))

	return int(value * pow(10,steps-1))

puzzles = open('puzzles.txt','wb+')
def getWordOver(difficulty):
	key = random.choice(words.keys())

	while True:
		if easiness(key) >= difficulty:
			break
		else:
			key = random.choice(words.keys())
			word = words[key]
	return key

def generate(bottomChoice):
	first = getWordOver(bottomChoice)
	second = getWordOver(bottomChoice)

	return (first,second,solve(first,second))

problems = 1000
while True:
	problem = generate(5200)
	first = problem[0]
	second = problem[1]
	solution = problem[2]
	
	if len(solution) == 0 or not solution:
		continue


	puzzles.write(first + ' ' + second + ' ' + str(len(solution)) + '\n')
	problems -= 1

	if problems == 0:
		break