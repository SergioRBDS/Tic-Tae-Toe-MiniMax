import numpy as np

def welcome():
    print("Bem vindo ao jogo, agora escolha")
    n = int(input("Numero de linhas: "))
    m = int(input("Numero de colunas: "))
    k = int(input("Tamanho da sequencia: "))
    return n, m, k
    
def jogada(mat,i,j,play):
    mat[i][j] = play

def main():
    #n,m,k = welcome()
    n = 3
    m = 3
    k = 3
    mat = np.full((n, m)," ")
    print(mat)
    return 0

if __name__ == "__main__":
    main()