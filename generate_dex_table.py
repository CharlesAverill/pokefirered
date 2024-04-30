import re
import json
from collections import defaultdict

file_path = "src/data/wild_encounters.json"
species_file_path = "include/constants/species.h"
evolution_file_path = "src/data/pokemon/evolution.h"

def get_sprite_path(species):
    return f"graphics/pokemon/{species.lower()}/front.png"

def format_map_name(map_name):
    map_name = map_name.replace("MAP_", "").replace("_", " ").replace("ROUTE", "ROUTE ").replace("ROOM", "ROOM ").title().strip()
    return map_name

def format_species(species):
    return species.replace("SPECIES_", "").title()

def get_species_order(file_path):
    species_order = []
    with open(file_path, "r", encoding="utf-8") as file:
        for line in file:
            if line.startswith("#define SPECIES_"):
                species = line.split()[1]
                species_order.append(species)
    return species_order[1:]

def get_evolution_data(evolution_file_path):
    evolution_data = defaultdict(list)
    with open(evolution_file_path, "r", encoding="utf-8") as file:
        for line in file:
            match = re.match(r"\s*\[SPECIES_(\w+)\]\s*=\s*\{\s*{(.*?)},", line)
            if match:
                species = format_species(match.group(1))
                evolution_info = match.group(2).strip()
                evolutions = [s[:-1] if s.endswith("}") else s for s in evolution_info.split("},")]
                for evo in evolutions:
                    evo_data = evo.split(",")
                    if len(evo_data) >= 2:
                        method = evo_data[0].strip()
                        target_species = format_species(evo_data[-1].strip())
                        if method == "EVO_LEVEL":
                            level = evo_data[1].strip()
                            evolution_data[target_species].append(f"Evolve from {species} at level {level}")
                        elif method.startswith("EVO_ITEM"):
                            item = " ".join(evo_data[1].split("_")[1:]).title()
                            evolution_data[target_species].append(f"Evolve from {species} using {item}")
                        else:
                            evolution_data[target_species].append(f"Evolve from {species} via high friendship")
    return evolution_data

event_pokemon = {
    "Mr_Mime": "Trade for Alakazam on Route 2",
    "Jynx": "Trade for Politoed in Cerulean City",
    "Nidoran_F": "Trade for Nidoking in Underground Path",
    "Nidoran_M": "Trade for Nidoqueen on Route 11",
    "Farfetchd": "Trade for Skarmory in Vermillion City",
    "Lickitung": "Trade for Ludicolo on Route 18",
    "Voltorb": "Trade for Manectric in the Pokemon Lab on Cinnabar Island",
    "Tangela": "Trade for Ariados in the Pokemon Lab on Cinnabar Island",
    "Seel": "Trade for Torkoal in the Pokemon Lab on Cinnabar Island",
    "Abra": "Game Corner",
    "Clefairy": "Game Corner",
    "Dratini": "Game Corner",
    "Scyther": "Game Corner",
    "Pinsir": "Game Corner",
    "Porygon": "Game Corner",
    "Omanyte": "Revive from Helix Fossil (Mt. Moon, Fossil Shop, Seafom Islands)",
    "Kabuto": "Revive from Dome Fossil (Mt. Moon, Fossil Shop, Seafom Islands)",
    "Aerodactyl": "Revive from Old Amber (Fossil Shop)",
    "Snorlax": "Route 16; Route 12",
    "Articuno": "Seafom Islands",
    "Zapdos": "Power Plant",
    "Moltres": "Mt. Ember",
    "Mewtwo": "Cerulean Cave",
    "Mew": "S.S. Anne Exterior",
    "Pichu": "Breed from Pikachu, Raichu",
    "Igglybuff": "Breed from Jigglypuff, Wigglytuff",
    "Elekid": "Breed from Electabuzz",
    "Raikou": "Roams after catching Latias",
    "Entei": "Roams after becoming Champion and speaking with Eunice in Fuschia",
    "Suicune": "Roams after catching Latios",
    "Lugia": "Navel Rock after becoming Champion and speaking with Captain Solomon on Five Island",
    "Ho_Oh": "Navel Rock after becoming Champion and speaking with Captain Solomon on Five Island",
    "Celebi": "Hemlock Forest after becoming Champion",
    "Shedinja": "Evolve from Nincada at level 20 with an extra slot in your party",
    "Lileep": "Revive from Root Fossil (Fossil Shop, Victory Road 3F)",
    "Anorith": "Revive from Claw Fossil (Fossil Shop, Diglett's Cave)",
    "Regirock": "Rock Peak Chamber in Diglett's Cave after becoming Champion",
    "Regice": "Iceberg Chamber in Icefall Cave after becoming Champion",
    "Registeel": "Iron Chamber in Dragon Gate after becoming Champion",
    "Kyogre": "Deepwater Cistern after becoming Champion",
    "Groudon": "Cinnabar Volcano after becoming Champion",
    "Rayquaza": "Gifted by Brendan after defeating him in Vermillion City after becoming Champion",
    "Latias": "Roams after catching Entei",
    "Latios": "Roams after catching Raikou",
    "Jirachi": "Pokemon Tower after becoming Champion and speaking to Mr. Fuji",
    "Deoxys": "Birth Island after becoming Champion, completing Captain Solomon's quest, and speaking with Prof. Charles in Saffron City"
}

try:
    with open(file_path, "r", encoding="utf-8") as file:
        data = json.load(file)["wild_encounter_groups"][0]["encounters"]
        
        # Dictionary to store encounter data grouped by map and species
        encounter_data = defaultdict(lambda: defaultdict(lambda: {"min_level": float('inf'), "max_level": float('-inf')}))
        species_locations = defaultdict(set)
        
        # Aggregate encounter data
        for encounter in data:
            map_name = format_map_name(encounter["map"])
            
            if "land_mons" in encounter:
                for land_mon in encounter["land_mons"]["mons"]:
                    species = format_species(land_mon['species'])
                    min_level = land_mon['min_level']
                    max_level = land_mon['max_level']
                    encounter_data[map_name][species]["min_level"] = min(min_level, encounter_data[map_name][species]["min_level"])
                    encounter_data[map_name][species]["max_level"] = max(max_level, encounter_data[map_name][species]["max_level"])
                    species_locations[species].add(map_name)
            
            if "water_mons" in encounter:
                for water_mon in encounter["water_mons"]["mons"]:
                    species = format_species(water_mon['species'])
                    min_level = water_mon['min_level']
                    max_level = water_mon['max_level']
                    encounter_data[map_name][species]["min_level"] = min(min_level, encounter_data[map_name][species]["min_level"])
                    encounter_data[map_name][species]["max_level"] = max(max_level, encounter_data[map_name][species]["max_level"])
                    species_locations[species].add(map_name)
            
            if "rock_smash_mons" in encounter:
                for rock_smash_mon in encounter["rock_smash_mons"]["mons"]:
                    species = format_species(rock_smash_mon['species'])
                    min_level = rock_smash_mon['min_level']
                    max_level = rock_smash_mon['max_level']
                    encounter_data[map_name][species]["min_level"] = min(min_level, encounter_data[map_name][species]["min_level"])
                    encounter_data[map_name][species]["max_level"] = max(max_level, encounter_data[map_name][species]["max_level"])
                    species_locations[species].add(map_name)
            
            if "fishing_mons" in encounter:
                for fishing_mon in encounter["fishing_mons"]["mons"]:
                    species = format_species(fishing_mon['species'])
                    min_level = fishing_mon['min_level']
                    max_level = fishing_mon['max_level']
                    encounter_data[map_name][species]["min_level"] = min(min_level, encounter_data[map_name][species]["min_level"])
                    encounter_data[map_name][species]["max_level"] = max(max_level, encounter_data[map_name][species]["max_level"])
                    species_locations[species].add(map_name)
        
        # Writing encounter data to encounters.html
        with open("changelog/encounters.html", "w", encoding="utf-8") as html_file:
            html_file.write("<!DOCTYPE html>\n<html>\n<head>\n<title>Wild Encounters</title>\n</head>\n<body>\n")
            
            for map_name, species_data in encounter_data.items():
                html_file.write(f"<h2>{map_name}</h2>\n")
                html_file.write("<table border='1'>\n")
                html_file.write("<tr><th>Sprite</th><th>Species</th><th>Min Level</th><th>Max Level</th></tr>\n")
                
                for species, level_data in species_data.items():
                    sprite_path = get_sprite_path(species)
                    html_file.write(f"<tr><td><img src='{sprite_path}' alt='{species}'></td><td>{species}</td><td>{level_data['min_level']}</td><td>{level_data['max_level']}</td></tr>\n")
                
                html_file.write("</table>\n")
                html_file.write("<hr>\n")
            
            html_file.write("</body>\n</html>")
        
        print("encounters.html generated successfully.")

        species_order = get_species_order(species_file_path)
        
        # Get evolution data
        evolution_data = get_evolution_data(evolution_file_path)
        
        # Writing species location data to locations.html
        with open("changelog/locations.html", "w", encoding="utf-8") as html_file:
            html_file.write("<!DOCTYPE html>\n<html>\n<head>\n<title>Species Locations</title>\n</head>\n<body>\n")
            
            for species in species_order:
                species = format_species(species)
                sprite_path = get_sprite_path(species)
                # if species in evolution_data or species in species_locations:
                html_file.write(f"<h2><img src='{sprite_path}' alt='{species}'>{species}</h2>\n")
                html_file.write("<ul>\n")
                if species in event_pokemon:
                    for location in event_pokemon[species].split(";"):
                        html_file.write(f"<li>{location}</li>\n")
                if species in evolution_data:
                    for evolution_info in evolution_data[species]:
                        html_file.write(f"<li>{evolution_info}</li>\n")
                html_file.write("</ul>\n")
                if species in species_locations:
                    locations = sorted(species_locations[species])
                    html_file.write("<table border='1'>\n")
                    html_file.write("<tr><th>Location</th><th>Min Level</th><th>Max Level</th></tr>\n")
                    for location in locations:
                        html_file.write(f"<tr><td>{location}</td><td>{encounter_data[location][species]['min_level']}</td><td>{encounter_data[location][species]['max_level']}</td></tr>\n")
                    html_file.write("</table>")
                html_file.write("<hr>\n")

                if species not in evolution_data and species not in species_locations and species not in event_pokemon:
                    print("Unaccounted for:", species)
            
            html_file.write("</body>\n</html>")
        
        print("locations.html generated successfully.")
        
except FileNotFoundError:
    print(f"File not found.")
except Exception as e:
    print(f"An error occurred: {e}")
