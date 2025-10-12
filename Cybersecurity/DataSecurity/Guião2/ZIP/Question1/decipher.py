substitutions = {
    "H": "a", 
    "P": "o", 
    "W": "r",
    "K": "p", 
    "F": "t",
    "R": "n",
    "D": "e",
    "T": "m",
    "N": "u",
    "L": "q",
    "O": "l",
    "A": "v",
    "J": "d",
    "Y": "c",
    "S": "f",
    "V": "i",
    "Q": "s",
    "I": "b",   
    "X": "h",
    "U": "x",
    "G": "z",
    "C": "g",
    "B": "j",
}


def countLetters(phrase):
    letters = {}
    for letter in phrase:
        if letter not in letters:
            letters[letter] = 0
        letters[letter] += 1        
    return letters


def countDigraphs(phrase):
    digraphs = {}
    for i in range(len(phrase) - 1):
        digraph = phrase[i:i + 2]
        if digraph not in digraphs:
            digraphs[digraph] = 0
        digraphs[digraph] += 1
    return digraphs

def countTrigraphs(phrase):
    trigraphs = {}
    for i in range(len(phrase) - 2):
        trigraph = phrase[i:i + 3]
        if trigraph not in trigraphs:
            trigraphs[trigraph] = 0
        trigraphs[trigraph] += 1
    return trigraphs


with open("ciphertext.txt") as f:
    phrase = f.read()

    # Find and substitute in phrase
    phrase = list(phrase)  # Convert to list so we can modify it

    for sub in substitutions:
        if len(sub) == 3:
            for i in range(len(phrase) - 2):
                phrase_trigraph = ''.join(phrase[i:i + 3])
                if phrase_trigraph == sub:
                    # print(phrase_trigraph)
                    phrase[i] = substitutions[sub][0]
                    phrase[i + 1] = substitutions[sub][1]
                    phrase[i + 2] = substitutions[sub][2]


    for sub in substitutions:
        if len(sub) == 2:
            for i in range(len(phrase) - 1):
                phrase_digraph = ''.join(phrase[i:i + 2])
                if phrase_digraph == sub:
                    # print(phrase_digraph)
                    phrase[i] = substitutions[sub][0]
                    phrase[i + 1] = substitutions[sub][1]
                    
    for sub in substitutions:
        if len(sub) == 1:
            for i in range(len(phrase)):
                if phrase[i] == sub:
                    phrase[i] = substitutions[sub]

    phrase = ''.join(phrase)  # Convert back to string

    print(phrase)
    letters = {k: v for k, v in sorted(countLetters(phrase).items(), key=lambda item: -item[1])}
    digraphs = {k: v for k, v in sorted(countDigraphs(phrase).items(), key=lambda item: item[1])}
    trigraphs = {k: v for k, v in sorted(countTrigraphs(phrase).items(), key=lambda item: item[1])}
    print(letters)
    print(digraphs)
    print(trigraphs)

    print(phrase)