#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Verif executable
if [ ! -f "./cub3D" ]; then
    echo -e "${RED}Erreur: L'exécutable cub3D n'existe pas.${NC}"
    echo "Veuillez compiler le projet d'abord."
    exit 1
fi

# Fonction test map
test_map() {
    local map=$1
    local expected_result=$2

    echo -e "\n${YELLOW}Testing: ${map}${NC}"
    ./cub3D "$map"
    result=$?

    if [ $expected_result -eq 0 ]; then
        if [ $result -eq 0 ]; then
            echo -e "${GREEN}✓ OK${NC}"
        else
            echo -e "${RED}✗ ERREUR: La map valide a échoué${NC}"
        fi
    else
        if [ $result -ne 0 ]; then
            echo -e "${GREEN}✓ OK (Erreur attendue)${NC}"
        else
            echo -e "${RED}✗ ERREUR: La map invalide n'a pas été rejetée${NC}"
        fi
    fi
}

# Test bonnes maps
echo -e "\n${YELLOW}=== Tests des maps valides ===${NC}"
if [ -d "test_maps/good" ]; then
    for map in test_maps/good/*; do
        if [ -f "$map" ]; then
            test_map "$map" 0
        fi
    done
else
    echo -e "${RED}Le dossier maps/good n'existe pas${NC}"
fi

# Test mauvaises maps
echo -e "\n${YELLOW}=== Tests des maps invalides ===${NC}"
if [ -d "test_maps/bad" ]; then
    for map in test_maps/bad/*; do
        if [ -f "$map" ]; then
            test_map "$map" 1
        fi
    done
else
    echo -e "${RED}Le dossier maps/bad n'existe pas${NC}"
fi