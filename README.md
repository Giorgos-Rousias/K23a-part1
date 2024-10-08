# K23a-part1
Πρώτο Παραδοτέο στο Ανάπτυξη Λογισμικού για Πληροφοριακά Συστήματα (K23a)


Steps to solve disk quota exceeded

1. Κλείνεις vscode και firefox αν είναι ανοιχτό.

2. Βρες τι τρώει χώρο:

        du -h | sort -h | tail -10 
    (αυτή η εντολή θέλει λίγο χρόνο)
συνήθεις ύποπτοι: .vscode-server, .vscode, .cache/Code
τα οποία τα διαγράφεις (πχ rm -rf .vscode-server) χωρίς να φοβάσαι, δεν έχουν κάτι σημαντικό.

3. Τρέχεις την εντολη 

        curl http://users.uoa.gr/~stef/vscode-config.sh | bash

4. problem solved :)


Εντολή για σύνδεση στα linux της σχολής μέσω terminal:

    ssh sdi1900166@linux08.di.uoa.gr
