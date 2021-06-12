from polyleven import levenshtein
import sys
import os

if __name__ == "__main__":
    path1 = sys.argv[1]
    path2 = sys.argv[2]

    seq1 = ''
    with open(path1, 'r') as f:
        seq1 = f.readline()

    seq2 = ''
    with open(path2, 'r') as f:
        seq2 = f.readline()



    dis = levenshtein(seq1, seq2)

    print("정확도: " +str(1-(dis/max(len(seq1), len(seq2)))) + "%")

    os.system("Pause")
