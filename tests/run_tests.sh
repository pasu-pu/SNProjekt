#!/bin/bash
# run_tests.sh - automatisierte Tests für das 'find'-Projekt
# Hinweis: Dieses Skript liegt im Verzeichnis "tests" und setzt das Arbeitsverzeichnis
# auf den Ordner "tests", sodass der relative Pfad zu ../find korrekt aufgelöst wird.

# Arbeitsverzeichnis auf das Verzeichnis des Skripts setzen
cd "$(dirname "$0")"

# Pfad zur ausführbaren Datei (im Projektstamm)
FIND_EXEC="../find"

# Überprüfe, ob die ausführbare Datei existiert und ausführbar ist
if [ ! -x "$FIND_EXEC" ]; then
    echo "Fehler: Das Programm 'find' wurde nicht gefunden. Bitte baue das Projekt mit 'make'."
    exit 1
fi

# Definiere die Testeingabe- und erwarteten Ausgabeverzeichnisse (relativ zu diesem Skript)
TEST_INPUT_DIR="test_input"
EXPECTED_DIR="expected"

# Überprüfe, ob das Testeingabeverzeichnis existiert
if [ ! -d "$TEST_INPUT_DIR" ]; then
    echo "Fehler: Testeingabeverzeichnis '$TEST_INPUT_DIR' existiert nicht. Bitte erstelle es und füge Testdateien/Verzeichnisse hinzu."
    exit 1
fi

# Überprüfe, ob das Verzeichnis für erwartete Ausgaben existiert
if [ ! -d "$EXPECTED_DIR" ]; then
    echo "Fehler: Erwartetes Ausgabeverzeichnis '$EXPECTED_DIR' existiert nicht. Bitte erstelle es und füge die erwarteten Output-Dateien hinzu."
    exit 1
fi

# ------------------------------
# Test 1: Basis-Suche ohne Threads
# ------------------------------
echo "Running Test 1: Basis-Suche ohne Threads..."
OUTPUT_FILE="output1.txt"
"$FIND_EXEC" -path "$TEST_INPUT_DIR" -name "test" -verbose > "$OUTPUT_FILE"

EXPECTED_OUTPUT="$EXPECTED_DIR/output1.txt"
if diff "$OUTPUT_FILE" "$EXPECTED_OUTPUT" > /dev/null; then
    echo "Test 1 passed!"
else
    echo "Test 1 FAILED: Ausgabe stimmt nicht mit der erwarteten Ausgabe überein."
    echo "Unterschiede:"
    diff "$OUTPUT_FILE" "$EXPECTED_OUTPUT"
fi

# ------------------------------
# Test 2: Suche mit aktivierten Threads
# ------------------------------
echo "Running Test 2: Suche mit aktivierten Threads..."
OUTPUT_FILE="output2.txt"
"$FIND_EXEC" -path "$TEST_INPUT_DIR" -name "test" -verbose -threads > "$OUTPUT_FILE"

EXPECTED_OUTPUT="$EXPECTED_DIR/output2.txt"
if diff "$OUTPUT_FILE" "$EXPECTED_OUTPUT" > /dev/null; then
    echo "Test 2 passed!"
else
    echo "Test 2 FAILED: Ausgabe stimmt nicht mit der erwarteten Ausgabe überein."
    echo "Unterschiede:"
    diff "$OUTPUT_FILE" "$EXPECTED_OUTPUT"
fi

# ------------------------------
# Test 3: Logdatei-Funktionalität
# ------------------------------
echo "Running Test 3: Logdatei-Funktionalität..."
LOG_FILE="output.log"
# Alte Logdatei löschen, falls vorhanden
rm -f "$LOG_FILE"
"$FIND_EXEC" -path "$TEST_INPUT_DIR" -name "test" -verbose -log "$LOG_FILE" > /dev/null

if [ -s "$LOG_FILE" ]; then
    echo "Test 3 passed! Logdatei '$LOG_FILE' wurde erstellt und enthält Daten."
else
    echo "Test 3 FAILED: Logdatei '$LOG_FILE' ist leer oder wurde nicht erstellt."
fi

echo "Alle Tests abgeschlossen."
