import argparse

parser = argparse.ArgumentParser()

parser.add_argument("notes", help="Notes", nargs='*')

args = parser.parse_args()

notes = list(map(int, args.notes))

if notes == []:
    print("Aucune moyenne à calculer")
else :
    
    valide = True

    for note in notes :
        if note < 0 or note > 20 :
            valide = False
            print(f"Note(s) non valide(s) : {note}")
        
    if valide :
        moyenne = sum(notes)/len(notes)

        print(f"Moyenne = {moyenne:.2f}")