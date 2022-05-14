#include "anno_tools.h"
#include "tools.h"

bool ReadAnnoString(uint64_t address, std::string& result)
{
    if (!address)
    {
        result = "[Could not retreive]";
        return false; 
    }

    uint64_t longString = *(uint64_t*)(address + 0x18);
    uint64_t length = *(uint64_t*)(address + 0x10);

    if (length > 64)
    {
        result = "[The name cannot be that long...]";
        return false;
    }

    bool isLong = longString > 0x7;

    wchar_t buffer[256];

    wchar_t* stringLocation = (wchar_t*)(address);

    if (isLong)
    {
        stringLocation = (wchar_t*)*(uint64_t*)(address);
    }

    wmemset(buffer, 0, _countof(buffer));
    wmemcpy(buffer, stringLocation, length);

    std::wstring wideString = buffer;
    std::string name = utf8_encode(wideString);
    
    if (name.length() <= 0)
    {
        if (isLong)
        {
            uint64_t p = *reinterpret_cast<uint64_t*>(address);
            result = "[HEXA-64] : " + p;
        }
        else
        {
            wchar_t p = *reinterpret_cast<wchar_t*>(address);
            result = "[HEXA-32] : " + p;
        }
        return false;
    }

    return true;
}

std::string GetNameFromGUID(uint64_t guid, bool& known)
{
    known = true;
    switch (guid)
    {
        case 0xf6961: return "Money";
        case 0xf6a0e: return "Influence";
        case 0xf6984: return "moderate workforce 1";
        case 0xf69c3: return "moderate workforce 2";
        case 0xf69c4: return "moderate workforce 3";
        case 0xf69c5: return "moderate workforce 4";
        case 0xf69d0: return "moderate workforce 5";
        case 0xf6abe: return "colony workforce 1";
        case 0xf6abf: return "colony workforce 2";
        case 0x1d4d4: return "market";
        case 0xf6aad: return "pub";
        case 0xf6aae: return "church";
        case 0xf6aaf: return "school";
        case 0xf6ab0: return "variety theatre";
        case 0xf6ab1: return "university";
        case 0xf6ab2: return "electric works";
        case 0xf6ab3: return "club house";
        case 0xf6ab4: return "bank";
        case 0x1d4f2: return "chapel";
        case 0xf6aac: return "Boxing Arena";
        case 0xf6a10: return "grain";
        case 0xf6a11: return "beef";
        case 0xf6a12: return "hops";
        case 0xf6a13: return "potatoes";
        case 0x1d4c8: return "wood";
        case 0xf6a15: return "wool";
        case 0xf6a17: return "pigs";
        case 0xf6a21: return "fur";
        case 0x1d4ce: return "grapes";
        case 0xf6a16: return "paprika";
        case 0xf6a18: return "fish";
        case 0xf6a38: return "salpeter";
        case 0xf6a34: return "quartz sand";
        case 0xf6a1a: return "concrete";
        case 0xf6a1b: return "soap";
        case 0xf6a14: return "timber";
        case 0xf6a1d: return "bricks";
        case 0xf6a47: return "fur coats";
        case 0xf6a1f: return "window";
        case 0xf6a20: return "light bulbs";
        case 0xf6a22: return "sailcloth";
        case 0xf6a23: return "chassis";
        case 0xf6a19: return "clay";
        case 0xf6a1e: return "sewing machines";
        case 0xf6a25: return "bread";
        case 0xf6a26: return "beer";
        case 0xf6a27: return "goulash";
        case 0xf6a29: return "canned food";
        case 0xf6a28: return "schnapps";
        case 0xf6a3e: return "sausage";
        case 0x1d4d0: return "champagne";
        case 0xf6a2a: return "beams";
        case 0xf6a2b: return "steel";
        case 0xf6a2d: return "weapons";
        case 0xf6a2e: return "dynamite";
        case 0xf6a2f: return "advanced weapons";
        case 0xf6a30: return "steam motors";
        case 0xf6a31: return "steam carriages";
        case 0xf6a1c: return "brass";
        case 0xf6a32: return "coal";
        case 0xf6a33: return "iron";
        case 0xf6a35: return "zinc";
        case 0xf6a36: return "copper";
        case 0xf6a37: return "cement";
        case 0xf6a39: return "gold ore";
        case 0xf6a3a: return "tallow";
        case 0xf6a3b: return "flour";
        case 0xf6a3c: return "malt";
        case 0xf6a3d: return "basic clothes";
        case 0xf6a41: return "glass";
        case 0xf6a42: return "inlay";
        case 0xf6a43: return "carbon filament";
        case 0xf6a46: return "pocket watch";
        case 0x1d4de: return "glasses";
        case 0xf6a48: return "phonographs";
        case 0xf6a49: return "gold";
        case 0xf6a4a: return "jewelry";
        case 0xf6a4b: return "sugar cane";
        case 0xf6a4c: return "tobacco";
        case 0xf6a4d: return "cotton";
        case 0xf6a4e: return "cocoa";
        case 0xf6a4f: return "caoutchouc";
        case 0x1d4df: return "coffee beans";
        case 0x1d4e2: return "corn";
        case 0x1d4e4: return "alpaca wool";
        case 0x1d4e9: return "bananas";
        case 0xf6a50: return "pearls";
        case 0x1d4ea: return "fish oil";
        case 0x1d4eb: return "ponchos";
        case 0x1d4ec: return "felt";
        case 0x1d4e5: return "bombin";
        case 0xf6a51: return "rum";
        case 0xf6a52: return "chocolate";
        case 0x1d4e0: return "coffee";
        case 0x1d4e1: return "fried bananas";
        case 0x1d4e3: return "burrito";
        case 0xf6a3f: return "sugar";
        case 0xf6a40: return "cotton cloth";
        case 0xf6a53: return "cigars";
        case 0x1d4d5: return "stone coal";
        case 0xf6b86: return "oil";
        case 0x1d4d6: return "electricity";
        case 0x1b786: return "scrap I";
        case 0x1b788: return "scrap II";
        case 0x1b78b: return "scrap III";
        case 0x1b80d: return "arctic workforce 1";
        case 0x1b80e: return "arctic workforce 2";
        case 0x1b844: return "heat from heater";
        case 0x1b835: return "post office";
        case 0x1c0ca: return "canteen";
        case 0x1b836: return "caribou meat";
        case 0x1b839: return "goose feathers";
        case 0x1b837: return "bear fur";
        case 0x1b83a: return "husky";
        case 0x1b83b: return "whale oil";
        case 0x1b838: return "seal skin";
        case 0x1b841: return "pemmican";
        case 0x1b83e: return "oil lamps";
        case 0x1b83d: return "sleeping bags";
        case 0x1b83c: return "parka";
        case 0x1b840: return "sled frames";
        case 0x1b83f: return "sleds";
        case 0x1b842: return "gas";
        case 0x1c50c: return "arctic scrap I";
        case 0x41db7: return "fuel state";
        case 0x41eda: return "fuel good";
        case 0x1bea4: return "africa workforce 1";
        case 0x1bea5: return "africa workforce 2";
        case 0x1e63e: return "africa workforce 3";
        case 0x1beb3: return "Bazaar";
        case 0x1beb9: return "Music Plaza";
        case 0x1beba: return "Monastery";
        case 0x1bef9: return "Radio Station";
        case 0x1beb4: return "Wanza Wood";
        case 0x1bebc: return "Hibiscus";
        case 0x1bebd: return "Flax";
        case 0x1bebf: return "Teff";
        case 0x1bec0: return "Indigo";
        case 0x1bec1: return "Spice";
        case 0x1bec2: return "Honey";
        case 0x1beb5: return "Sanga";
        case 0x1bec3: return "Goat Milk";
        case 0x1beb6: return "Salt";
        case 0x1cbc6: return "Paper";
        case 0x1cfc8: return "Seafood";
        case 0x1bed7: return "Linen";
        case 0x1bee8: return "Spiced Teff Flour";
        case 0x1cbc5: return "Candles";
        case 0x1befd: return "Ammunition";
        case 0x1bf01: return "Perfume Extract";
        case 0x1befb: return "Decorated Cloth";
        case 0x1beb7: return "Dried Meat";
        case 0x1bee1: return "Woven Clothes";
        case 0x1bed6: return "Tea";
        case 0x1bee2: return "Mud Bricks";
        case 0x1cfc4: return "Ceramics";
        case 0x1bee4: return "Tapestries";
        case 0x1beea: return "Spicy Stew";
        case 0x1beee: return "Tobacco Pipe";
        case 0x1cbc2: return "Scriptures";
        case 0x1cbc3: return "Lanterns";
        case 0x1befc: return "Leather Shoes";
        case 0x1befe: return "Suits";
        case 0x1beff: return "Telephones";
        case 0x1d260: return "Research";
        case 0x20673: return "Tourist Workforce";
        case 0x2083f: return "Jam";
        case 0x2083d: return "Shampoo";
        case 0x20841: return "Lemonade";
        case 0x2099c: return "Souvenier";
        case 0x207e5: return "Cinnamon";
        case 0x207e7: return "Coconut Butter";
        case 0x207e9: return "Citrus Fruits";
        case 0x20dd8: return "Camphor";
        case 0x20ddf: return "Elevator";
        case 0x2103d: return "Biscuits";
        case 0x2103e: return "Typewriter";
        case 0x20fae: return "Resin";
        case 0x20faf: return "Cherry Wood";
        case 0x20fd9: return "LacquerColor";
        case 0x21042: return "Cognac";
        case 0x21041: return "Violin";
        case 0x21040: return "Billiard";
        case 0x2103f: return "Toys";
        case 0x21012: return "Gum";
        case 0x20fda: return "Ethanol";
        case 0x20fee: return "Celluloid";
        case 0x21288: return "ToasterMonumentNeed";
        case 0x212c4: return "TableWareMonumentNeed";
        case 0x212c5: return "VaccumCleanerMonumentNeed";
        case 0x212c6: return "FridgeMonumentNeed";
        case 0x212c7: return "BagsMonumentNeed";
        case 0x212c8: return "BankersLampMonumentNeed";
        case 0x212c9: return "ParaventMonumentNeed";
        case 0x212ca: return "DeskMonumentNeed";
        case 0x212cb: return "BedMonumentNeed";
        case 0x212cc: return "ChairMonumentNeed";
        case 0x212cd: return "ToothPasteMonumentNeed";
        case 0x212ce: return "CleanerMonumentNeed";
        case 0x212cf: return "LipstickMonumentNeed";
        case 0x212d0: return "FaceCreamMonumentNeed";
        case 0x212d1: return "PomadeMonumentNeed";
        case 0x20fc4: return "DepartmentStoreNeed";
        case 0x20fc3: return "FurnitureStoreNeed";
        case 0x20fc5: return "PharmacyNeed";
        case 0xf6a45: return "Penny Farthings";
    }

    known = false;
    return "[Unkown]";
}

uint64_t GetGuidFromName(std::string name)
{
    unsigned int name_crc32 = crc_update(0, name.c_str(), name.size());
    switch (name_crc32)
    {
        case COMPILE_TIME_CRC32_STR("Money"): return 0xf6961;
        case COMPILE_TIME_CRC32_STR("Influence"): return 0xf6a0e;
        case COMPILE_TIME_CRC32_STR("moderate workforce 1"): return 0xf6984;
        case COMPILE_TIME_CRC32_STR("moderate workforce 2"): return 0xf69c3;
        case COMPILE_TIME_CRC32_STR("moderate workforce 3"): return 0xf69c4;
        case COMPILE_TIME_CRC32_STR("moderate workforce 4"): return 0xf69c5;
        case COMPILE_TIME_CRC32_STR("moderate workforce 5"): return 0xf69d0;
        case COMPILE_TIME_CRC32_STR("colony workforce 1"): return 0xf6abe;
        case COMPILE_TIME_CRC32_STR("colony workforce 2"): return 0xf6abf;
        case COMPILE_TIME_CRC32_STR("market"): return 0x1d4d4;
        case COMPILE_TIME_CRC32_STR("pub"): return 0xf6aad;
        case COMPILE_TIME_CRC32_STR("church"): return 0xf6aae;
        case COMPILE_TIME_CRC32_STR("school"): return 0xf6aaf;
        case COMPILE_TIME_CRC32_STR("variety theatre"): return 0xf6ab0;
        case COMPILE_TIME_CRC32_STR("university"): return 0xf6ab1;
        case COMPILE_TIME_CRC32_STR("electric works"): return 0xf6ab2;
        case COMPILE_TIME_CRC32_STR("club house"): return 0xf6ab3;
        case COMPILE_TIME_CRC32_STR("bank"): return 0xf6ab4;
        case COMPILE_TIME_CRC32_STR("chapel"): return 0x1d4f2;
        case COMPILE_TIME_CRC32_STR("Boxing Arena"): return 0xf6aac;
        case COMPILE_TIME_CRC32_STR("grain"): return 0xf6a10;
        case COMPILE_TIME_CRC32_STR("beef"): return 0xf6a11;
        case COMPILE_TIME_CRC32_STR("hops"): return 0xf6a12;
        case COMPILE_TIME_CRC32_STR("potatoes"): return 0xf6a13;
        case COMPILE_TIME_CRC32_STR("wood"): return 0x1d4c8;
        case COMPILE_TIME_CRC32_STR("wool"): return 0xf6a15;
        case COMPILE_TIME_CRC32_STR("pigs"): return 0xf6a17;
        case COMPILE_TIME_CRC32_STR("fur"): return 0xf6a21;
        case COMPILE_TIME_CRC32_STR("grapes"): return 0x1d4ce;
        case COMPILE_TIME_CRC32_STR("paprika"): return 0xf6a16;
        case COMPILE_TIME_CRC32_STR("fish"): return 0xf6a18;
        case COMPILE_TIME_CRC32_STR("salpeter"): return 0xf6a38;
        case COMPILE_TIME_CRC32_STR("quartz sand"): return 0xf6a34;
        case COMPILE_TIME_CRC32_STR("concrete"): return 0xf6a1a;
        case COMPILE_TIME_CRC32_STR("soap"): return 0xf6a1b;
        case COMPILE_TIME_CRC32_STR("timber"): return 0xf6a14;
        case COMPILE_TIME_CRC32_STR("bricks"): return 0xf6a1d;
        case COMPILE_TIME_CRC32_STR("fur coats"): return 0xf6a47;
        case COMPILE_TIME_CRC32_STR("window"): return 0xf6a1f;
        case COMPILE_TIME_CRC32_STR("light bulbs"): return 0xf6a20;
        case COMPILE_TIME_CRC32_STR("sailcloth"): return 0xf6a22;
        case COMPILE_TIME_CRC32_STR("chassis"): return 0xf6a23;
        case COMPILE_TIME_CRC32_STR("clay"): return 0xf6a19;
        case COMPILE_TIME_CRC32_STR("sewing machines"): return 0xf6a1e;
        case COMPILE_TIME_CRC32_STR("bread"): return 0xf6a25;
        case COMPILE_TIME_CRC32_STR("beer"): return 0xf6a26;
        case COMPILE_TIME_CRC32_STR("goulash"): return 0xf6a27;
        case COMPILE_TIME_CRC32_STR("canned food"): return 0xf6a29;
        case COMPILE_TIME_CRC32_STR("schnapps"): return 0xf6a28;
        case COMPILE_TIME_CRC32_STR("sausage"): return 0xf6a3e;
        case COMPILE_TIME_CRC32_STR("champagne"): return 0x1d4d0;
        case COMPILE_TIME_CRC32_STR("beams"): return 0xf6a2a;
        case COMPILE_TIME_CRC32_STR("steel"): return 0xf6a2b;
        case COMPILE_TIME_CRC32_STR("weapons"): return 0xf6a2d;
        case COMPILE_TIME_CRC32_STR("dynamite"): return 0xf6a2e;
        case COMPILE_TIME_CRC32_STR("advanced weapons"): return 0xf6a2f;
        case COMPILE_TIME_CRC32_STR("steam motors"): return 0xf6a30;
        case COMPILE_TIME_CRC32_STR("steam carriages"): return 0xf6a31;
        case COMPILE_TIME_CRC32_STR("brass"): return 0xf6a1c;
        case COMPILE_TIME_CRC32_STR("coal"): return 0xf6a32;
        case COMPILE_TIME_CRC32_STR("iron"): return 0xf6a33;
        case COMPILE_TIME_CRC32_STR("zinc"): return 0xf6a35;
        case COMPILE_TIME_CRC32_STR("copper"): return 0xf6a36;
        case COMPILE_TIME_CRC32_STR("cement"): return 0xf6a37;
        case COMPILE_TIME_CRC32_STR("gold ore"): return 0xf6a39;
        case COMPILE_TIME_CRC32_STR("tallow"): return 0xf6a3a;
        case COMPILE_TIME_CRC32_STR("flour"): return 0xf6a3b;
        case COMPILE_TIME_CRC32_STR("malt"): return 0xf6a3c;
        case COMPILE_TIME_CRC32_STR("basic clothes"): return 0xf6a3d;
        case COMPILE_TIME_CRC32_STR("glass"): return 0xf6a41;
        case COMPILE_TIME_CRC32_STR("inlay"): return 0xf6a42;
        case COMPILE_TIME_CRC32_STR("carbon filament"): return 0xf6a43;
        case COMPILE_TIME_CRC32_STR("pocket watch"): return 0xf6a46;
        case COMPILE_TIME_CRC32_STR("glasses"): return 0x1d4de;
        case COMPILE_TIME_CRC32_STR("phonographs"): return 0xf6a48;
        case COMPILE_TIME_CRC32_STR("gold"): return 0xf6a49;
        case COMPILE_TIME_CRC32_STR("jewelry"): return 0xf6a4a;
        case COMPILE_TIME_CRC32_STR("sugar cane"): return 0xf6a4b;
        case COMPILE_TIME_CRC32_STR("tobacco"): return 0xf6a4c;
        case COMPILE_TIME_CRC32_STR("cotton"): return 0xf6a4d;
        case COMPILE_TIME_CRC32_STR("cocoa"): return 0xf6a4e;
        case COMPILE_TIME_CRC32_STR("caoutchouc"): return 0xf6a4f;
        case COMPILE_TIME_CRC32_STR("coffee beans"): return 0x1d4df;
        case COMPILE_TIME_CRC32_STR("corn"): return 0x1d4e2;
        case COMPILE_TIME_CRC32_STR("alpaca wool"): return 0x1d4e4;
        case COMPILE_TIME_CRC32_STR("bananas"): return 0x1d4e9;
        case COMPILE_TIME_CRC32_STR("pearls"): return 0xf6a50;
        case COMPILE_TIME_CRC32_STR("fish oil"): return 0x1d4ea;
        case COMPILE_TIME_CRC32_STR("ponchos"): return 0x1d4eb;
        case COMPILE_TIME_CRC32_STR("felt"): return 0x1d4ec;
        case COMPILE_TIME_CRC32_STR("bombin"): return 0x1d4e5;
        case COMPILE_TIME_CRC32_STR("rum"): return 0xf6a51;
        case COMPILE_TIME_CRC32_STR("chocolate"): return 0xf6a52;
        case COMPILE_TIME_CRC32_STR("coffee"): return 0x1d4e0;
        case COMPILE_TIME_CRC32_STR("fried bananas"): return 0x1d4e1;
        case COMPILE_TIME_CRC32_STR("burrito"): return 0x1d4e3;
        case COMPILE_TIME_CRC32_STR("sugar"): return 0xf6a3f;
        case COMPILE_TIME_CRC32_STR("cotton cloth"): return 0xf6a40;
        case COMPILE_TIME_CRC32_STR("cigars"): return 0xf6a53;
        case COMPILE_TIME_CRC32_STR("stone coal"): return 0x1d4d5;
        case COMPILE_TIME_CRC32_STR("oil"): return 0xf6b86;
        case COMPILE_TIME_CRC32_STR("electricity"): return 0x1d4d6;
        case COMPILE_TIME_CRC32_STR("scrap I"): return 0x1b786;
        case COMPILE_TIME_CRC32_STR("scrap II"): return 0x1b788;
        case COMPILE_TIME_CRC32_STR("scrap III"): return 0x1b78b;
        case COMPILE_TIME_CRC32_STR("arctic workforce 1"): return 0x1b80d;
        case COMPILE_TIME_CRC32_STR("arctic workforce 2"): return 0x1b80e;
        case COMPILE_TIME_CRC32_STR("heat from heater"): return 0x1b844;
        case COMPILE_TIME_CRC32_STR("post office"): return 0x1b835;
        case COMPILE_TIME_CRC32_STR("canteen"): return 0x1c0ca;
        case COMPILE_TIME_CRC32_STR("caribou meat"): return 0x1b836;
        case COMPILE_TIME_CRC32_STR("goose feathers"): return 0x1b839;
        case COMPILE_TIME_CRC32_STR("bear fur"): return 0x1b837;
        case COMPILE_TIME_CRC32_STR("husky"): return 0x1b83a;
        case COMPILE_TIME_CRC32_STR("whale oil"): return 0x1b83b;
        case COMPILE_TIME_CRC32_STR("seal skin"): return 0x1b838;
        case COMPILE_TIME_CRC32_STR("pemmican"): return 0x1b841;
        case COMPILE_TIME_CRC32_STR("oil lamps"): return 0x1b83e;
        case COMPILE_TIME_CRC32_STR("sleeping bags"): return 0x1b83d;
        case COMPILE_TIME_CRC32_STR("parka"): return 0x1b83c;
        case COMPILE_TIME_CRC32_STR("sled frames"): return 0x1b840;
        case COMPILE_TIME_CRC32_STR("sleds"): return 0x1b83f;
        case COMPILE_TIME_CRC32_STR("gas"): return 0x1b842;
        case COMPILE_TIME_CRC32_STR("arctic scrap I"): return 0x1c50c;
        case COMPILE_TIME_CRC32_STR("fuel state"): return 0x41db7;
        case COMPILE_TIME_CRC32_STR("fuel good"): return 0x41eda;
        case COMPILE_TIME_CRC32_STR("africa workforce 1"): return 0x1bea4;
        case COMPILE_TIME_CRC32_STR("africa workforce 2"): return 0x1bea5;
        case COMPILE_TIME_CRC32_STR("africa workforce 3"): return 0x1e63e;
        case COMPILE_TIME_CRC32_STR("Bazaar"): return 0x1beb3;
        case COMPILE_TIME_CRC32_STR("Music Plaza"): return 0x1beb9;
        case COMPILE_TIME_CRC32_STR("Monastery"): return 0x1beba;
        case COMPILE_TIME_CRC32_STR("Radio Station"): return 0x1bef9;
        case COMPILE_TIME_CRC32_STR("Wanza Wood"): return 0x1beb4;
        case COMPILE_TIME_CRC32_STR("Hibiscus"): return 0x1bebc;
        case COMPILE_TIME_CRC32_STR("Flax"): return 0x1bebd;
        case COMPILE_TIME_CRC32_STR("Teff"): return 0x1bebf;
        case COMPILE_TIME_CRC32_STR("Indigo"): return 0x1bec0;
        case COMPILE_TIME_CRC32_STR("Spice"): return 0x1bec1;
        case COMPILE_TIME_CRC32_STR("Honey"): return 0x1bec2;
        case COMPILE_TIME_CRC32_STR("Sanga"): return 0x1beb5;
        case COMPILE_TIME_CRC32_STR("Goat Milk"): return 0x1bec3;
        case COMPILE_TIME_CRC32_STR("Salt"): return 0x1beb6;
        case COMPILE_TIME_CRC32_STR("Paper"): return 0x1cbc6;
        case COMPILE_TIME_CRC32_STR("Seafood"): return 0x1cfc8;
        case COMPILE_TIME_CRC32_STR("Linen"): return 0x1bed7;
        case COMPILE_TIME_CRC32_STR("Spiced Teff Flour"): return 0x1bee8;
        case COMPILE_TIME_CRC32_STR("Candles"): return 0x1cbc5;
        case COMPILE_TIME_CRC32_STR("Ammunition"): return 0x1befd;
        case COMPILE_TIME_CRC32_STR("Perfume Extract"): return 0x1bf01;
        case COMPILE_TIME_CRC32_STR("Decorated Cloth"): return 0x1befb;
        case COMPILE_TIME_CRC32_STR("Dried Meat"): return 0x1beb7;
        case COMPILE_TIME_CRC32_STR("Woven Clothes"): return 0x1bee1;
        case COMPILE_TIME_CRC32_STR("Tea"): return 0x1bed6;
        case COMPILE_TIME_CRC32_STR("Mud Bricks"): return 0x1bee2;
        case COMPILE_TIME_CRC32_STR("Ceramics"): return 0x1cfc4;
        case COMPILE_TIME_CRC32_STR("Tapestries"): return 0x1bee4;
        case COMPILE_TIME_CRC32_STR("Spicy Stew"): return 0x1beea;
        case COMPILE_TIME_CRC32_STR("Tobacco Pipe"): return 0x1beee;
        case COMPILE_TIME_CRC32_STR("Scriptures"): return 0x1cbc2;
        case COMPILE_TIME_CRC32_STR("Lanterns"): return 0x1cbc3;
        case COMPILE_TIME_CRC32_STR("Leather Shoes"): return 0x1befc;
        case COMPILE_TIME_CRC32_STR("Suits"): return 0x1befe;
        case COMPILE_TIME_CRC32_STR("Telephones"): return 0x1beff;
        case COMPILE_TIME_CRC32_STR("Research"): return 0x1d260;
        case COMPILE_TIME_CRC32_STR("Tourist Workforce"): return 0x20673;
        case COMPILE_TIME_CRC32_STR("Jam"): return 0x2083f;
        case COMPILE_TIME_CRC32_STR("Shampoo"): return 0x2083d;
        case COMPILE_TIME_CRC32_STR("Lemonade"): return 0x20841;
        case COMPILE_TIME_CRC32_STR("Souvenier"): return 0x2099c;
        case COMPILE_TIME_CRC32_STR("Cinnamon"): return 0x207e5;
        case COMPILE_TIME_CRC32_STR("Coconut Butter"): return 0x207e7;
        case COMPILE_TIME_CRC32_STR("Citrus Fruits"): return 0x207e9;
        case COMPILE_TIME_CRC32_STR("Camphor"): return 0x20dd8;
        case COMPILE_TIME_CRC32_STR("Elevator"): return 0x20ddf;
        case COMPILE_TIME_CRC32_STR("Biscuits"): return 0x2103d;
        case COMPILE_TIME_CRC32_STR("Typewriter"): return 0x2103e;
        case COMPILE_TIME_CRC32_STR("Resin"): return 0x20fae;
        case COMPILE_TIME_CRC32_STR("Cherry Wood"): return 0x20faf;
        case COMPILE_TIME_CRC32_STR("LacquerColor"): return 0x20fd9;
        case COMPILE_TIME_CRC32_STR("Cognac"): return 0x21042;
        case COMPILE_TIME_CRC32_STR("Violin"): return 0x21041;
        case COMPILE_TIME_CRC32_STR("Billiard"): return 0x21040;
        case COMPILE_TIME_CRC32_STR("Toys"): return 0x2103f;
        case COMPILE_TIME_CRC32_STR("Gum"): return 0x21012;
        case COMPILE_TIME_CRC32_STR("Ethanol"): return 0x20fda;
        case COMPILE_TIME_CRC32_STR("Celluloid"): return 0x20fee;
        case COMPILE_TIME_CRC32_STR("ToasterMonumentNeed"): return 0x21288;
        case COMPILE_TIME_CRC32_STR("TableWareMonumentNeed"): return 0x212c4;
        case COMPILE_TIME_CRC32_STR("VaccumCleanerMonumentNeed"): return 0x212c5;
        case COMPILE_TIME_CRC32_STR("FridgeMonumentNeed"): return 0x212c6;
        case COMPILE_TIME_CRC32_STR("BagsMonumentNeed"): return 0x212c7;
        case COMPILE_TIME_CRC32_STR("BankersLampMonumentNeed"): return 0x212c8;
        case COMPILE_TIME_CRC32_STR("ParaventMonumentNeed"): return 0x212c9;
        case COMPILE_TIME_CRC32_STR("DeskMonumentNeed"): return 0x212ca;
        case COMPILE_TIME_CRC32_STR("BedMonumentNeed"): return 0x212cb;
        case COMPILE_TIME_CRC32_STR("ChairMonumentNeed"): return 0x212cc;
        case COMPILE_TIME_CRC32_STR("ToothPasteMonumentNeed"): return 0x212cd;
        case COMPILE_TIME_CRC32_STR("CleanerMonumentNeed"): return 0x212ce;
        case COMPILE_TIME_CRC32_STR("LipstickMonumentNeed"): return 0x212cf;
        case COMPILE_TIME_CRC32_STR("FaceCreamMonumentNeed"): return 0x212d0;
        case COMPILE_TIME_CRC32_STR("PomadeMonumentNeed"): return 0x212d1;
        case COMPILE_TIME_CRC32_STR("DepartmentStoreNeed"): return 0x20fc4;
        case COMPILE_TIME_CRC32_STR("FurnitureStoreNeed"): return 0x20fc3;
        case COMPILE_TIME_CRC32_STR("PharmacyNeed"): return 0x20fc5;
        case COMPILE_TIME_CRC32_STR("Penny Farthings"): return 0xf6a45;
    }

    return 0;
}
