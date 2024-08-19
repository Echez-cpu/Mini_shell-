#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

char *ersetze(char *string, char *neuer_string_teil, int start_alter_string, int länge_alter_string) {
    // Berechne die Länge des neuen Strings
    size_t neue_laenge = strlen(string) - länge_alter_string + strlen(neuer_string_teil) + 1; // +1 für das Null-Byte

    // Allokiere Speicher für den neuen String
    char *neuer_string = (char*)malloc(neue_laenge);
    if (neuer_string == NULL) {
        perror("Speicherzuweisung fehlgeschlagen");
        return NULL;
    }

    // Kopiere den Anfang des alten Strings
    ft_strlcpy(neuer_string, string, start_alter_string + 1); // +1, um das Null-Byte am Ende des Kopierteils zu berücksichtigen

    // Kopiere den neuen Teil
    ft_strlcpy(neuer_string + start_alter_string, neuer_string_teil, neue_laenge - start_alter_string);

	// Kopiere den Rest des alten Strings
    ft_strlcpy(neuer_string + start_alter_string + strlen(neuer_string_teil), string + start_alter_string + länge_alter_string, neue_laenge - start_alter_string - strlen(neuer_string_teil));

    // Gib die alten Strings frei
    free(string);
    free(neuer_string_teil);

    return neuer_string;
}

int	main(int argc, char **argv, char **env)
{
	if(argv[1]!=NULL)
		printf("%s\n", ersetze(ft_strdup("Hello, this world is huge!"), ft_strdup(argv[1]), 12, 5));
	
}