#!/bin/bash

# Couleurs pour le formatage
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Vérifier si l'exécutable existe
if [ ! -f "./cub3D" ]; then
    echo -e "${RED}Erreur: L'exécutable cub3D n'existe pas.${NC}"
    echo "Veuillez compiler le projet d'abord."
    exit 1
fi

# Fonction pour tester une map
test_map() {
    local map=$1
    local expected_result=$2  # 0 pour les bonnes maps, différent de 0 pour les mauvaises

    echo -e "\n${YELLOW}Testing: ${map}${NC}"

    # Exécution sans Valgrind
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

    # Exécution avec Valgrind
    echo -e "${YELLOW}Running Valgrind...${NC}"
    valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes --trace-children=yes ./cub3D "$map"
    valgrind_result=$?

    if [ $valgrind_result -eq 0 ]; then
        echo -e "${GREEN}Valgrind: Pas de problème détecté${NC}"
    else
        echo -e "${RED}Valgrind: Problèmes détectés (voir les détails ci-dessus)${NC}"
    fi
}

# Test des bonnes maps
echo -e "\n${YELLOW}=== Tests des maps valides ===${NC}"
if [ -d "maps/good" ]; then
    for map in maps/good/*; do
        if [ -f "$map" ]; then
            test_map "$map" 0
        fi
    done
else
    echo -e "${RED}Le dossier maps/good n'existe pas${NC}"
fi

# Test des mauvaises maps
echo -e "\n${YELLOW}=== Tests des maps invalides ===${NC}"
if [ -d "maps/bad" ]; then
    for map in maps/bad/*; do
        if [ -f "$map" ]; then
            test_map "$map" 1
        fi
    done
else
    echo -e "${RED}Le dossier maps/bad n'existe pas${NC}"
fi
