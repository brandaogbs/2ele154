# meme mimimimi

def gera_meme(texto):
    meme = ""
    for letra in texto:
        if letra in "aeiouAEIOU":
            meme += 'i'
        else:
            meme += letra

    return meme

print(gera_meme("Voce precisa mudar esse seu jeito"))