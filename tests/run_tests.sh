#!/bin/bash
# run_tests.sh - automatisierte Tests für das 'find'-Projekt
# Dieses Skript führt mehrere Testfälle aus, um die Funktionalität des Programms zu prüfen.

# Prüfe, ob das ausführbare Programm 'find' existiert.
if [ ! -x "./find" ]; then
    echo "Fehler: Das Programm 'find' wurde nicht gefunden. Bitte baue das Projekt mit 'make'."
    exit 1
fi

# Verzeichnis für Testeingaben (muss existieren)
TEST_INPUT_DIR="tests/test_input"
if [ ! -d "$TEST_INPUT_DIR" ]; then
    echo "Fehler: Testeingabeverzeichnis '$TEST_INPUT_DIR' existiert nicht. Bitte erstelle es und füge Testdateien/Verzeichnisse hinzu."
    exit 1
fi

# Verzeichnis für erwartete Ausgaben
EXPECTED_DIR="tests/expected"
if [ ! -d "$EXPECTED_DIR" ]; then
    echo "Fehler: Erwartetes Ausgabeverzeichnis '$EXPECTED_DIR' existiert nicht. Bitte erstelle es und füge die erwarteten Output-Dateien hinzu."
    exit 1
fi

# ------------------------------
# Test 1: Basis-Suche ohne Threads
# ------------------------------
echo "Running Test 1: Basis-Suche ohne Threads ..."
OUTPUT_FILE="tests/output1.txt"
./find -path "$TEST_INPUT_DIR" -name "test" -verbose > "$OUTPUT_FILE"

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
echo "Running Test 2: Suche mit aktivierten Threads ..."
OUTPUT_FILE="tests/output2.txt"
./find -path "$TEST_INPUT_DIR" -name "test" -verbose -threads > "$OUTPUT_FILE"

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
echo "Running Test 3: Logdatei-Funktionalität ..."
LOG_FILE="tests/output.log"
# Alte Logdatei löschen, falls vorhanden
rm -f "$LOG_FILE"
./find -path "$TEST_INPUT_DIR" -name "test" -verbose -log "$LOG_FILE" > /dev/null

if [ -s "$LOG_FILE" ]; then
    echo "Test 3 passed! Logdatei '$LOG_FILE' wurde erstellt und enthält Daten."
else
    echo "Test 3 FAILED: Logdatei '$LOG_FILE' ist leer oder wurde nicht erstellt."
fi

echo "Alle Tests abgeschlossen."
