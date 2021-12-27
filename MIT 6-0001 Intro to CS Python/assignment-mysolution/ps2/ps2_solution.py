import string

def is_word_guessed(secret_word, letters_guessed):
    for letter in secret_word:
        if letter not in letters_guessed:
            return False
    return True

def test_is_word_guessed():
    secret_word = 'apple'
    letters_guessed = ['e', 'i', 'k', 'p', 'r', 's']
    assert is_word_guessed(secret_word, letters_guessed) == False, 'test_is_word_guessed FAILED!'

test_is_word_guessed()

def get_guessed_word(secret_word, letters_guessed):
    res = ''
    for letter in secret_word:
        if letter in letters_guessed:
            res += letter
        else:
            res += '_ '
    return res

def test_get_guessed_word():
    secret_word = 'apple'
    letters_guessed = ['e', 'i', 'k', 'p', 'r', 's']
    assert get_guessed_word(secret_word, letters_guessed) == '_ pp_ e', 'test_get_guessed_word FAILED!'

test_get_guessed_word()

def get_available_letters(letters_guessed):
    return ''.join(sorted(list(set(string.ascii_lowercase) - set(letters_guessed))))

def test_get_available_letters():
    letters_guessed = ['e', 'i', 'k', 'p', 'r', 's']
    assert get_available_letters(letters_guessed) == 'abcdfghjlmnoqtuvwxyz', 'test_get_available_letters FAILED!'

test_get_available_letters()

