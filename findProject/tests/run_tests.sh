#!/bin/bash
# run_tests.sh - automatisierte Tests für das 'find'-Projekt mit sortiertem Vergleich
# Dieses Skript liegt im Verzeichnis "tests" und setzt das Arbeitsverzeichnis auf "tests".

# Arbeitsverzeichnis auf das Verzeichnis des Skripts setzen
cd "$(dirname "$0")"

# Pfad zur ausführbaren Datei (im Projektstamm)
FIND_EXEC="../find"

if [ ! -x "$FIND_EXEC" ]; then
    echo "Fehler: Das Programm 'find' wurde nicht gefunden. Bitte baue das Projekt mit 'make'."
    exit 1
fi

# Definiere die Testeingabe- und erwarteten Ausgabeverzeichnisse
TEST_INPUT_DIR="test_input"
EXPECTED_DIR="expected"

if [ ! -d "$TEST_INPUT_DIR" ]; then
    echo "Fehler: Testeingabeverzeichnis '$TEST_INPUT_DIR' existiert nicht. Bitte erstelle es und füge Testdateien/Verzeichnisse hinzu."
    exit 1
fi

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
# Sortiere Ausgabe und erwartete Datei
sort "$OUTPUT_FILE" > sorted_output1.txt
sort "$EXPECTED_DIR/output1.txt" > sorted_expected_output1.txt
if diff sorted_output1.txt sorted_expected_output1.txt > /dev/null; then
    echo "Test 1 passed!"
else
    echo "Test 1 FAILED: Ausgabe stimmt nicht mit der erwarteten Ausgabe überein."
    echo "Unterschiede:"
    diff sorted_output1.txt sorted_expected_output1.txt
fi

# ------------------------------
# Test 2: Suche mit aktivierten Threads
# ------------------------------
echo "Running Test 2: Suche mit aktivierten Threads..."
OUTPUT_FILE="output2.txt"
"$FIND_EXEC" -path "$TEST_INPUT_DIR" -name "test" -verbose -threads > "$OUTPUT_FILE"
# Sortiere Ausgabe und erwartete Datei
sort "$OUTPUT_FILE" > sorted_output2.txt
sort "$EXPECTED_DIR/output2.txt" > sorted_expected_output2.txt
if diff sorted_output2.txt sorted_expected_output2.txt > /dev/null; then
    echo "Test 2 passed!"
else
    echo "Test 2 FAILED: Ausgabe stimmt nicht mit der erwarteten Ausgabe überein."
    echo "Unterschiede:"
    diff sorted_output2.txt sorted_expected_output2.txt
fi

# ------------------------------
# Test 3: Logdatei-Funktionalität
# ------------------------------
echo "Running Test 3: Logdatei-Funktionalität..."
LOG_FILE="output.log"
rm -f "$LOG_FILE"
"$FIND_EXEC" -path "$TEST_INPUT_DIR" -name "test" -verbose -log "$LOG_FILE" > /dev/null

if [ -s "$LOG_FILE" ]; then
    echo "Test 3 passed! Logdatei '$LOG_FILE' wurde erstellt und enthält Daten."
else
    echo "Test 3 FAILED: Logdatei '$LOG_FILE' ist leer oder wurde nicht erstellt."
fi

echo "Alle Tests abgeschlossen."
