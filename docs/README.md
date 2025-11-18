# Week10_FilterCSVbyAge
Programmets formål er at filtrere data i en fil baseret på brugerens input.
Data skal være navne på personer og aldrene på disse. 
Programmet tjekker hver linje for, om den indeholder en gyldig alder som andet argument.
Linjer med en gyldig alder under den indtastede maksimum alder gemmes i den ønskede output-fil.
Linjer med fejl (tom linje, manglende alder, ugyldig alder) gemmes ikke, og en tilhørende fejlmeddelelse printes i terminalen.

# Input
Programmet læser en fil med kommaseparerede værdier (.csv) og tager følgende kommandoer:
[alder] [input-fil] [output-fil]

alder:      Den maksimum alder, der ønskes filtreret efter.
input-fil:  Filen indeholdende data til sortering.
output-fil: Den ønskede output-fil (eksempelvis .txt) til de sorterede data.
            Eksisterer den ikke, bliver den oprettet.

# Output
Gyldige linjer outputtes til en fil efter brugerens ønske (som angivet med [output-fil]) i den rækkefølge, de oprindeligt stod i. Et tekstfilformat som f.eks. .txt er at foretrække.
Alle filtyper kan i teorien skrives som output, og der vil blive genereret en fil med dataene.
Vælges en ikke-tekstfil (f.eks. .png), vil man dog få problemer med at åbne den.

# Filer
main.c
compile_flags.txt
launch.json
tasks.json
README.md
.gitignore