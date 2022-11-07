NBR_ELEVES = 3

class Etudiant():
    def __init__(self, nom, age, notes):
        self.nom = nom
        self.age = age
        self.notes = notes
        self.moyenne = 0

eleves = []

for _ in range(NBR_ELEVES):
    nom = input("Entrer le nom de l'élève: ")
    age = int(input("Entrer l'age de l'élève: "))
    notes = [int(input("Entrer une note : ")) for _ in range(3)]
    eleves.append(Etudiant(nom, age, notes))

# Calcule de la moyenne, de la meilleure note et de la moins bonne note

moyenne = 0
note_min = 21
note_max = 0

for eleve in eleves:
    
    # Scrap de toutes les notes pour la pire et la meilleure
    for note in eleve.notes:
        # Meilleure note
        if note > note_max :
            note_max = note
        
        # Pire note
        if note < note_min:
            note_min = note
    
    moyenne += sum(eleve.notes)

print(f"La moyenne est de : {moyenne/len(eleves*3)} et les notes vont de {note_min} à {note_max}")