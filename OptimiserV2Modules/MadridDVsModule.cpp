//
// Created by a1091793 on 19/01/18.
//

#include "MadridDVsModule.hpp"
#include <pugixml.hpp>
#include <cmath>


void addPointElementMadrid(pugi::xml_node & node, int x_val, double & y_val)
{
    pugi::xml_node elmnt = node.append_child("point");
    elmnt.append_attribute("x").set_value(x_val);
    elmnt.append_attribute("y").set_value(y_val);

}

void setExpRuleMadrid(pugi::xml_document & doc, int lu_index, int function_index, double I, double a, double b)
{
    std::string xpath_query =
        "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@name=\"MB_Rules\"]/RulesBlock/Rules/value/vector/elem[" +
            std::to_string(function_index) + "]/vector/elem[" + std::to_string(lu_index) + "]/spline";
    pugi::xpath_node_set nodes = doc.select_nodes(xpath_query.c_str());
    pugi::xml_node parentNode = nodes.begin()->parent();
    for (pugi::xpath_node_set::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        pugi::xpath_node node = *it;
        parentNode.remove_child(node.node());
    }
    pugi::xml_node new_parent = parentNode.append_child("spline");
    addPointElementMadrid(new_parent, 0, I);

//            // Calculate exponential decay values
    double y1 = a * exp(-b * 1);
    double y2 = a * exp(-b * 2);
    double y3 = a * exp(-b * 3);
    double y4 = a * exp(-b * 4);
    double y5 = a * exp(-b * 5);
    double y6 = a * exp(-b * 6);
    double y7 = a * exp(-b * 7);
    // double //y8=a*exp(-b*8);
    // Calculate absolute values of exponential decay
    double z1 = std::abs(y1);
    double z2 = std::abs(y2);
    double z3 = std::abs(y3);
    double z4 = std::abs(y4);
    double z5 = std::abs(y5);
    double z6 = std::abs(y6);
    double z7 = std::abs(y7);

    double default_y = 0.0;
    if (z1 > 0.0001) {
        addPointElementMadrid(new_parent, 1, y1);
    } else {
        addPointElementMadrid(new_parent, 1, default_y);
    }
    if (z2 > 0.0001) {
        addPointElementMadrid(new_parent, 2, y2);
    } else {
        addPointElementMadrid(new_parent, 2, default_y);
    }
    if (z3 > 0.0001) {
        addPointElementMadrid(new_parent, 3, (y3));
    } else {
        addPointElementMadrid(new_parent, 3, default_y);
    }
    // Add
    if (z4 > 0.0001) {
        addPointElementMadrid(new_parent, 4, (y4));
    } else {
        addPointElementMadrid(new_parent, 4, default_y);
    }
    if (z5 > 0.0001) {
        addPointElementMadrid(new_parent, 5, (y5));
    } else {
        addPointElementMadrid(new_parent, 5, default_y);
    }
    if (z6 > 0.0001) {
        addPointElementMadrid(new_parent, 6, (y6));
    } else {
        addPointElementMadrid(new_parent, 6, default_y);
    }
    if (z7 > 0.0001) {
        addPointElementMadrid(new_parent, 7, (y7));
    } else {
        addPointElementMadrid(new_parent, 7, default_y);
    }
    addPointElementMadrid(new_parent, 8, default_y);

}

template <typename T> void
setAllValuesXMLNodeMadrid(pugi::xml_document & doc, std::string xpath_query, T new_value)
{
    pugi::xpath_node_set nodes = doc.select_nodes(xpath_query.c_str());
    for (pugi::xpath_node_set::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        pugi::xpath_node node = *it;
        node.node().first_child().set_value(std::to_string(new_value).c_str());
    }
}



void
geoprojectEditMadrid(const boost::filesystem::path & geoproj_path, const std::vector<double> & dvs)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(geoproj_path.string().c_str());
    //// Parameters - Self-Influence Neighbourhood Rules
    // Arable land (Function Class 1)
    // From ARAble land to ARAble land
    double araara1 = dvs[0];
    double araara2 = dvs[1];
    double araara3 = dvs[2];
    // Permanent crops (Function Class 2)
    // From PERmanent crops to PERmanent crops
    double perper1 = dvs[3];
    double perper2 = dvs[4];
    double perper3 = dvs[5];
    // Pastures (Function Class 3)
    // From PAStures to PAStures
    double paspas1 = dvs[6];
    double paspas2 = dvs[7];
    double paspas3 = dvs[8];
    // Agricultural areas (Function Class 4)
    // From AGRicultural areas to AGRicultural areas
    double agragr1 = dvs[9];
    double agragr2 = dvs[10];
    double agragr3 = dvs[11];
    // Residential (Function Class 5)
    // From RESidential to RESidential
    double resres1 = dvs[12];
    double resres2 = dvs[13];
    double resres3 = dvs[14];
    // Industry & commerce (Function class 6)
    // From INDustry & commerce to INDustry & commerce
    double indind1 = dvs[15];
    double indind2 = dvs[16];
    double indind3 = dvs[17];
    // Recreation areas (Function class 7)
    // From RECreation areas to RECreation areas
    double recrec1 = dvs[18];
    double recrec2 = dvs[19];
    double recrec3 = dvs[20];
    // Forest (Function class 8)
    // From FORest to FORest
    double forfor1 = dvs[21];
    double forfor2 = dvs[22];
    double forfor3 = dvs[23];

    //// Parameters - Interaction Neighbourhood Rules
    // Arable land (Function Class 1)
    // From NATural areas to ARAble land
    double natara1 = dvs[24];
    double natara2 = dvs[25];
    double natara3 = dvs[26];
    // From From PERmanent crops to ARAble land
    double perara1 = dvs[27];
    double perara2 = dvs[28];
    double perara3 = dvs[29];
    // From PAStures to ARAble land
    double pasara1 = dvs[30];
    double pasara2 = dvs[31];
    double pasara3 = dvs[32];
    // From AGRicultural areas to ARAble land
    double agrara1 = dvs[33];
    double agrara2 = dvs[34];
    double agrara3 = dvs[35];
    // From RESidential to ARAble land
    double resara1 = dvs[36];
    double resara2 = dvs[37];
    double resara3 = dvs[38];
    // From INDustry & commerce to ARAble land
    double indara1 = dvs[39];
    double indara2 = dvs[40];
    double indara3 = dvs[41];
    // From RECreation areas to ARAble land
    double recara1 = dvs[42];
    double recara2 = dvs[43];
    double recara3 = dvs[44];
    // From FORest to ARAble land
    double forara1 = dvs[45];
    double forara2 = dvs[46];
    double forara3 = dvs[47];
    // From ROAd & rail to ARAble land
    double roaara1 = dvs[48];
    double roaara2 = dvs[49];
    double roaara3 = dvs[50];
    // From AIRports to ARAble land
    double airara1 = dvs[51];
    double airara2 = dvs[52];
    double airara3 = dvs[53];
    // From MINe and dump sites to ARAble land
    double minara1 = dvs[54];
    double minara2 = dvs[55];
    double minara3 = dvs[56];
    // From FREsh water to ARAble land
    double freara1 = dvs[57];
    double freara2 = dvs[58];
    double freara3 = dvs[59];

    // Permanent crops (Function Class 2)
    // From NATural areas to PERmanent crops
    double natper1 = dvs[60];
    double natper2 = dvs[61];
    double natper3 = dvs[62];
    // From ARAble land to PERmanent crops
    double araper1 = dvs[63];
    double araper2 = dvs[64];
    double araper3 = dvs[65];
    // From PAStures to PERmanent crops
    double pasper1 = dvs[66];
    double pasper2 = dvs[67];
    double pasper3 = dvs[68];
    // From AGRicultural areas to PERmanent crops
    double agrper1 = dvs[69];
    double agrper2 = dvs[70];
    double agrper3 = dvs[71];
    // From RESidential to PERmanent crops
    double resper1 = dvs[72];
    double resper2 = dvs[73];
    double resper3 = dvs[74];
    // From INDustry & commerce to PERmanent crops
    double indper1 = dvs[75];
    double indper2 = dvs[76];
    double indper3 = dvs[77];
    // From RECreation areas to PERmanent crops
    double recper1 = dvs[78];
    double recper2 = dvs[79];
    double recper3 = dvs[80];
    // From FORest to PERmanent crops
    double forper1 = dvs[81];
    double forper2 = dvs[82];
    double forper3 = dvs[83];
    // From ROAd & rail to PERmanent crops
    double roaper1 = dvs[84];
    double roaper2 = dvs[85];
    double roaper3 = dvs[86];
    // From AIRports to PERmanent crops
    double airper1 = dvs[87];
    double airper2 = dvs[88];
    double airper3 = dvs[89];
    // From MINe & dump sites to PERmanent crops
    double minper1 = dvs[90];
    double minper2 = dvs[91];
    double minper3 = dvs[92];
    // From FREsh water to PERmanent crops
    double freper1 = dvs[93];
    double freper2 = dvs[94];
    double freper3 = dvs[95];

    // Pastures (Function Class 3)
    // From NATural areas to PAStures
    double natpas1 = dvs[96];
    double natpas2 = dvs[97];
    double natpas3 = dvs[98];
    // From ARAble land to PAStures
    double arapas1 = dvs[99];
    double arapas2 = dvs[100];
    double arapas3 = dvs[101];
    // From PERmanent crops to PAStures
    double perpas1 = dvs[102];
    double perpas2 = dvs[103];
    double perpas3 = dvs[104];
    // From AGRicultural areas to PAStures
    double agrpas1 = dvs[105];
    double agrpas2 = dvs[106];
    double agrpas3 = dvs[107];
    // From RESidential to PAStures
    double respas1 = dvs[108];
    double respas2 = dvs[109];
    double respas3 = dvs[110];
    // From INDustry & commerce to PAStures
    double indpas1 = dvs[111];
    double indpas2 = dvs[112];
    double indpas3 = dvs[113];
    // From RECreation areas to PAStures
    double recpas1 = dvs[114];
    double recpas2 = dvs[115];
    double recpas3 = dvs[116];
    // From FORest to PAStures
    double forpas1 = dvs[117];
    double forpas2 = dvs[118];
    double forpas3 = dvs[119];
    // From ROAd & rail to PAStures
    double roapas1 = dvs[120];
    double roapas2 = dvs[121];
    double roapas3 = dvs[122];
    // From AIRports to PAStures
    double airpas1 = dvs[123];
    double airpas2 = dvs[124];
    double airpas3 = dvs[125];
    // From MINe & dump sites to PAStures
    double minpas1 = dvs[126];
    double minpas2 = dvs[127];
    double minpas3 = dvs[128];
    // From FREsh water to PAStures
    double frepas1 = dvs[129];
    double frepas2 = dvs[130];
    double frepas3 = dvs[131];

    // Agricultural areas (Function Class 4)
    // From NATural areas to AGRicultural areas
    double natagr1 = dvs[132];
    double natagr2 = dvs[133];
    double natagr3 = dvs[134];
    // From ARAble land to AGRicultural areas
    double araagr1 = dvs[135];
    double araagr2 = dvs[136];
    double araagr3 = dvs[137];
    // From PERmanent crops to AGRicultural areas
    double peragr1 = dvs[138];
    double peragr2 = dvs[139];
    double peragr3 = dvs[140];
    // From PAStures to AGRicultural areas
    double pasagr1 = dvs[141];
    double pasagr2 = dvs[142];
    double pasagr3 = dvs[143];
    // From RESidential to AGRicultural areas
    double resagr1 = dvs[144];
    double resagr2 = dvs[145];
    double resagr3 = dvs[146];
    // From INDustry & commerce to AGRicultural areas
    double indagr1 = dvs[147];
    double indagr2 = dvs[148];
    double indagr3 = dvs[149];
    // From RECreation areas to AGRicultural areas
    double recagr1 = dvs[150];
    double recagr2 = dvs[151];
    double recagr3 = dvs[152];
    // From FORest to AGRicultural areas
    double foragr1 = dvs[153];
    double foragr2 = dvs[154];
    double foragr3 = dvs[155];
    // From ROAd & rail to AGRicultural areas
    double roaagr1 = dvs[156];
    double roaagr2 = dvs[157];
    double roaagr3 = dvs[158];
    // From AIRports to AGRicultural areas
    double airagr1 = dvs[159];
    double airagr2 = dvs[160];
    double airagr3 = dvs[161];
    // From MINe & dump sites to AGRicultural areas
    double minagr1 = dvs[162];
    double minagr2 = dvs[163];
    double minagr3 = dvs[164];
    // From FREsh water to AGRicultural areas
    double freagr1 = dvs[165];
    double freagr2 = dvs[166];
    double freagr3 = dvs[167];

    // Residential (Function Class 5)
    // From NATural areas to RESidential
    double natres1 = dvs[168];
    double natres2 = dvs[169];
    double natres3 = dvs[170];
    // From ARAble land to RESidential
    double arares1 = dvs[171];
    double arares2 = dvs[172];
    double arares3 = dvs[173];
    // From PERmanent crops to RESidential
    double perres1 = dvs[174];
    double perres2 = dvs[175];
    double perres3 = dvs[176];
    // From PAStures to RESidential
    double pasres1 = dvs[177];
    double pasres2 = dvs[178];
    double pasres3 = dvs[179];
    // From AGRicultural areas to RESidential
    double agrres1 = dvs[180];
    double agrres2 = dvs[181];
    double agrres3 = dvs[182];
    // From INDustry & commerce to RESidential
    double indres1 = dvs[183];
    double indres2 = dvs[184];
    double indres3 = dvs[185];
    // From RECreation areas to RESidential
    double recres1 = dvs[186];
    double recres2 = dvs[187];
    double recres3 = dvs[188];
    // From FORest to RESidential
    double forres1 = dvs[189];
    double forres2 = dvs[190];
    double forres3 = dvs[191];
    // From ROAd & rail to RESidential
    double roares1 = dvs[192];
    double roares2 = dvs[193];
    double roares3 = dvs[194];
    // From AIRports to RESidential
    double airres1 = dvs[195];
    double airres2 = dvs[196];
    double airres3 = dvs[197];
    // From MINe & dump sites to RESidential
    double minres1 = dvs[198];
    double minres2 = dvs[199];
    double minres3 = dvs[200];
    // From FREsh water to RESidential
    double freres1 = dvs[201];
    double freres2 = dvs[202];
    double freres3 = dvs[203];

    // Industry & commerce (Function class 6)
    // From NATural areas to INDustry & commerce
    double natind1 = dvs[204];
    double natind2 = dvs[205];
    double natind3 = dvs[206];
    // From ARAble land to INDustry & commerce
    double araind1 = dvs[207];
    double araind2 = dvs[208];
    double araind3 = dvs[209];
    // From PERmanent crops to INDustry & commerce
    double perind1 = dvs[210];
    double perind2 = dvs[211];
    double perind3 = dvs[212];
    // From PAStures to INDustry & commerce
    double pasind1 = dvs[213];
    double pasind2 = dvs[214];
    double pasind3 = dvs[215];
    // From AGRicultural areas to INDustry & commerce
    double agrind1 = dvs[216];
    double agrind2 = dvs[217];
    double agrind3 = dvs[218];
    // From RESidential to INDustry & commerce
    double resind1 = dvs[219];
    double resind2 = dvs[220];
    double resind3 = dvs[221];
    // From RECreation areas to INDustry & commerce
    double recind1 = dvs[222];
    double recind2 = dvs[223];
    double recind3 = dvs[224];
    // From FORest to INDustry & commerce
    double forind1 = dvs[225];
    double forind2 = dvs[226];
    double forind3 = dvs[227];
    // From ROAd & rail to INDustry & commerce
    double roaind1 = dvs[228];
    double roaind2 = dvs[229];
    double roaind3 = dvs[230];
    // From AIRports to INDustry & commerce
    double airind1 = dvs[231];
    double airind2 = dvs[232];
    double airind3 = dvs[233];
    // From MINe & dump sites to INDustry & commerce
    double minind1 = dvs[234];
    double minind2 = dvs[235];
    double minind3 = dvs[236];
    // From FREsh water to INDustry & commerce
    double freind1 = dvs[237];
    double freind2 = dvs[238];
    double freind3 = dvs[239];

    // Recreation areas (Function class 7)
    // From NATural areas to RECreation areas
    double natrec1 = dvs[240];
    double natrec2 = dvs[241];
    double natrec3 = dvs[242];
    // From ARAble land to RECreation areas
    double ararec1 = dvs[243];
    double ararec2 = dvs[244];
    double ararec3 = dvs[245];
    // From PERmanent crops to RECreation areas
    double perrec1 = dvs[246];
    double perrec2 = dvs[247];
    double perrec3 = dvs[248];
    // From PAStures to RECreation areas
    double pasrec1 = dvs[249];
    double pasrec2 = dvs[250];
    double pasrec3 = dvs[251];
    // From AGRicultural areas to RECreation areas
    double agrrec1 = dvs[252];
    double agrrec2 = dvs[253];
    double agrrec3 = dvs[254];
    // From RESidential to RECreation areas
    double resrec1 = dvs[255];
    double resrec2 = dvs[256];
    double resrec3 = dvs[257];
    // From INDusty & commerce to RECreation areas
    double indrec1 = dvs[258];
    double indrec2 = dvs[259];
    double indrec3 = dvs[260];
    // From FORest to RECreation areas
    double forrec1 = dvs[261];
    double forrec2 = dvs[262];
    double forrec3 = dvs[263];
    // From ROAd & rail to RECreation areas
    double roarec1 = dvs[264];
    double roarec2 = dvs[265];
    double roarec3 = dvs[266];
    // From AIRports to RECreation areas
    double airrec1 = dvs[267];
    double airrec2 = dvs[268];
    double airrec3 = dvs[269];
    // From MINe & dump sites to RECreation areas
    double minrec1 = dvs[270];
    double minrec2 = dvs[271];
    double minrec3 = dvs[272];
    // From FREsh water to RECreation areas
    double frerec1 = dvs[273];
    double frerec2 = dvs[274];
    double frerec3 = dvs[275];

    // Forest (class 8)
    // From NATural areas to FORest
    double natfor1 = dvs[276];
    double natfor2 = dvs[277];
    double natfor3 = dvs[278];
    // From ARAble land to FORest
    double arafor1 = dvs[279];
    double arafor2 = dvs[280];
    double arafor3 = dvs[281];
    // From PERmanent crops to FORest
    double perfor1 = dvs[282];
    double perfor2 = dvs[283];
    double perfor3 = dvs[284];
    // From PAStures to FORest
    double pasfor1 = dvs[285];
    double pasfor2 = dvs[286];
    double pasfor3 = dvs[287];
    // From AGRicultural areas to FORest
    double agrfor1 = dvs[288];
    double agrfor2 = dvs[289];
    double agrfor3 = dvs[290];
    // From RESidential to FORest
    double resfor1 = dvs[291];
    double resfor2 = dvs[292];
    double resfor3 = dvs[293];
    // From INDusty & commerce to FORest
    double indfor1 = dvs[294];
    double indfor2 = dvs[295];
    double indfor3 = dvs[296];
    // From RECreation areas to FORest
    double recfor1 = dvs[297];
    double recfor2 = dvs[298];
    double recfor3 = dvs[299];
    // From ROAd & rail to FORest
    double roafor1 = dvs[300];
    double roafor2 = dvs[301];
    double roafor3 = dvs[302];
    // From AIRports to FORest
    double airfor1 = dvs[303];
    double airfor2 = dvs[304];
    double airfor3 = dvs[305];
    // From MINe & dump sites to FORest
    double minfor1 = dvs[306];
    double minfor2 = dvs[307];
    double minfor3 = dvs[308];
    // From FREsh water to FORest
    double frefor1 = dvs[309];
    double frefor2 = dvs[310];
    double frefor3 = dvs[311];

    //// Parameters - Accessibility distance decay
    // ARAble land
    double aramdd = dvs[312];
    // PERmanent crops
    double permdd = dvs[313];
    // PAStures
    double pasmdd = dvs[314];
    // AGRicultural areas
    double agrmdd = dvs[315];
    // RESidential
    double resmdd = dvs[316];
    // INDustry & commerce
    double indmdd = dvs[317];
    // RECreation areas
    double recmdd = dvs[318];
    // FORest
    double formdd = dvs[319];
    //// Parameters - Accessibility Weights
    // ARAble land
    double aramwe = dvs[320];
    // PERmanent crops
    double permwe = dvs[321];
    // PAStures
    double pasmwe = dvs[322];
    // AGRicultural areas
    double agrmwe = dvs[323];
    // RESidential
    double resmwe = dvs[324];
    // INDustry & commerce
    double indmwe = dvs[325];
    // RECreation areas
    double recmwe = dvs[326];
    // FORest
    double formwe = dvs[327];

    //	%Amend Self-influence Neighbourhood Rules
    // Arable land
    setExpRuleMadrid(doc, 2, 1, araara1, araara2, araara3);
    // Permanent crops
    setExpRuleMadrid(doc, 3, 2, perper1, perper2, perper3);
    // Pastures
    setExpRuleMadrid(doc, 4, 3, paspas1, paspas2, paspas3);
    // Agricultural areas
    setExpRuleMadrid(doc, 5, 4, agragr1, agragr2, agragr3);
    // Residential
    setExpRuleMadrid(doc, 6, 5, resres1, resres2, resres3);
    // Industry & commerce
    setExpRuleMadrid(doc, 7, 6, indind1, indind2, indind3);
    // Recreation areas
    setExpRuleMadrid(doc, 8, 7, recrec1, recrec2, recrec3);
    // Forest
    setExpRuleMadrid(doc, 9, 8, forfor1, forfor2, forfor3);

    //	%Amend Iteraction Neighbourhood Rules
    // Arable land
    setExpRuleMadrid(doc, 1, 1, natara1, natara2, natara3);
    setExpRuleMadrid(doc, 3, 1, perara1, perara2, perara3);
    setExpRuleMadrid(doc, 4, 1, pasara1, pasara2, pasara3);
    setExpRuleMadrid(doc, 5, 1, agrara1, agrara2, agrara3);
    setExpRuleMadrid(doc, 6, 1, resara1, resara2, resara3);
    setExpRuleMadrid(doc, 7, 1, indara1, indara2, indara3);
    setExpRuleMadrid(doc, 8, 1, recara1, recara2, recara3);
    setExpRuleMadrid(doc, 9, 1, forara1, forara2, forara3);
    setExpRuleMadrid(doc, 10, 1, roaara1, roaara2, roaara3);
    setExpRuleMadrid(doc, 12, 1, airara1, airara2, airara3);
    setExpRuleMadrid(doc, 13, 1, minara1, minara2, minara3);
    setExpRuleMadrid(doc, 14, 1, freara1, freara2, freara3);
    // Permanent crops
    setExpRuleMadrid(doc, 1, 2, natper1, natper2, natper3);
    setExpRuleMadrid(doc, 2, 2, araper1, araper2, araper3);
    setExpRuleMadrid(doc, 4, 2, pasper1, pasper2, pasper3);
    setExpRuleMadrid(doc, 5, 2, agrper1, agrper2, agrper3);
    setExpRuleMadrid(doc, 6, 2, resper1, resper2, resper3);
    setExpRuleMadrid(doc, 7, 2, indper1, indper2, indper3);
    setExpRuleMadrid(doc, 8, 2, recper1, recper2, recper3);
    setExpRuleMadrid(doc, 9, 2, forper1, forper2, forper3);
    setExpRuleMadrid(doc, 10, 2, roaper1, roaper2, roaper3);
    setExpRuleMadrid(doc, 12, 2, airper1, airper2, airper3);
    setExpRuleMadrid(doc, 13, 2, minper1, minper2, minper3);
    setExpRuleMadrid(doc, 14, 2, freper1, freper2, freper3);
    // Pastures
    setExpRuleMadrid(doc, 1, 3, natpas1, natpas2, natpas3);
    setExpRuleMadrid(doc, 2, 3, arapas1, arapas2, arapas3);
    setExpRuleMadrid(doc, 3, 3, perpas1, perpas2, perpas3);
    setExpRuleMadrid(doc, 5, 3, agrpas1, agrpas2, agrpas3);
    setExpRuleMadrid(doc, 6, 3, respas1, respas2, respas3);
    setExpRuleMadrid(doc, 7, 3, indpas1, indpas2, indpas3);
    setExpRuleMadrid(doc, 8, 3, recpas1, recpas2, recpas3);
    setExpRuleMadrid(doc, 9, 3, forpas1, forpas2, forpas3);
    setExpRuleMadrid(doc, 10, 3, roapas1, roapas2, roapas3);
    setExpRuleMadrid(doc, 12, 3, airpas1, airpas2, airpas3);
    setExpRuleMadrid(doc, 13, 3, minpas1, minpas2, minpas3);
    setExpRuleMadrid(doc, 14, 3, frepas1, frepas2, frepas3);
    // Agricultural areas
    setExpRuleMadrid(doc, 1, 4, natagr1, natagr2, natagr3);
    setExpRuleMadrid(doc, 2, 4, araagr1, araagr2, araagr3);
    setExpRuleMadrid(doc, 3, 4, peragr1, peragr2, peragr3);
    setExpRuleMadrid(doc, 4, 4, pasagr1, pasagr2, pasagr3);
    setExpRuleMadrid(doc, 6, 4, resagr1, resagr2, resagr3);
    setExpRuleMadrid(doc, 7, 4, indagr1, indagr2, indagr3);
    setExpRuleMadrid(doc, 8, 4, recagr1, recagr2, recagr3);
    setExpRuleMadrid(doc, 9, 4, foragr1, foragr2, foragr3);
    setExpRuleMadrid(doc, 10, 4, roaagr1, roaagr2, roaagr3);
    setExpRuleMadrid(doc, 12, 4, airagr1, airagr2, airagr3);
    setExpRuleMadrid(doc, 13, 4, minagr1, minagr2, minagr3);
    setExpRuleMadrid(doc, 14, 4, freagr1, freagr2, freagr3);
    // Residential
    setExpRuleMadrid(doc, 1, 5, natres1, natres2, natres3);
    setExpRuleMadrid(doc, 2, 5, arares1, arares2, arares3);
    setExpRuleMadrid(doc, 3, 5, perres1, perres2, perres3);
    setExpRuleMadrid(doc, 4, 5, pasres1, pasres2, pasres3);
    setExpRuleMadrid(doc, 5, 5, agrres1, agrres2, agrres3);
    setExpRuleMadrid(doc, 7, 5, indres1, indres2, indres3);
    setExpRuleMadrid(doc, 8, 5, recres1, recres2, recres3);
    setExpRuleMadrid(doc, 9, 5, forres1, forres2, forres3);
    setExpRuleMadrid(doc, 10, 5, roares1, roares2, roares3);
    setExpRuleMadrid(doc, 12, 5, airres1, airres2, airres3);
    setExpRuleMadrid(doc, 13, 5, minres1, minres2, minres3);
    setExpRuleMadrid(doc, 14, 5, freres1, freres2, freres3);
    // Industry & commerce
    setExpRuleMadrid(doc, 1, 6, natind1, natind2, natind3);
    setExpRuleMadrid(doc, 2, 6, araind1, araind2, araind3);
    setExpRuleMadrid(doc, 3, 6, perind1, perind2, perind3);
    setExpRuleMadrid(doc, 4, 6, pasind1, pasind2, pasind3);
    setExpRuleMadrid(doc, 5, 6, agrind1, agrind2, agrind3);
    setExpRuleMadrid(doc, 6, 6, resind1, resind2, resind3);
    setExpRuleMadrid(doc, 8, 6, recind1, recind2, recind3);
    setExpRuleMadrid(doc, 9, 6, forind1, forind2, forind3);
    setExpRuleMadrid(doc, 10, 6, roaind1, roaind2, roaind3);
    setExpRuleMadrid(doc, 12, 6, airind1, airind2, airind3);
    setExpRuleMadrid(doc, 13, 6, minind1, minind2, minind3);
    setExpRuleMadrid(doc, 14, 6, freind1, freind2, freind3);
    // Recreation areas
    setExpRuleMadrid(doc, 1, 7, natrec1, natrec2, natrec3);
    setExpRuleMadrid(doc, 2, 7, ararec1, ararec2, ararec3);
    setExpRuleMadrid(doc, 3, 7, perrec1, perrec2, perrec3);
    setExpRuleMadrid(doc, 4, 7, pasrec1, pasrec2, pasrec3);
    setExpRuleMadrid(doc, 5, 7, agrrec1, agrrec2, agrrec3);
    setExpRuleMadrid(doc, 6, 7, resrec1, resrec2, resrec3);
    setExpRuleMadrid(doc, 7, 7, indrec1, indrec2, indrec3);
    setExpRuleMadrid(doc, 9, 7, forrec1, forrec2, forrec3);
    setExpRuleMadrid(doc, 10, 7, roarec1, roarec2, roarec3);
    setExpRuleMadrid(doc, 12, 7, airrec1, airrec2, airrec3);
    setExpRuleMadrid(doc, 13, 7, minrec1, minrec2, minrec3);
    setExpRuleMadrid(doc, 14, 7, frerec1, frerec2, frerec3);
    // Forest
    setExpRuleMadrid(doc, 1, 8, natfor1, natfor2, natfor3);
    setExpRuleMadrid(doc, 2, 8, arafor1, arafor2, arafor3);
    setExpRuleMadrid(doc, 3, 8, perfor1, perfor2, perfor3);
    setExpRuleMadrid(doc, 4, 8, pasfor1, pasfor2, pasfor3);
    setExpRuleMadrid(doc, 5, 8, agrfor1, agrfor2, agrfor3);
    setExpRuleMadrid(doc, 6, 8, resfor1, resfor2, resfor3);
    setExpRuleMadrid(doc, 7, 8, indfor1, indfor2, indfor3);
    setExpRuleMadrid(doc, 8, 8, recfor1, recfor2, recfor3);
    setExpRuleMadrid(doc, 10, 8, roafor1, roafor2, roafor3);
    setExpRuleMadrid(doc, 12, 8, airfor1, airfor2, airfor3);
    setExpRuleMadrid(doc, 13, 8, minfor1, minfor2, minfor3);
    setExpRuleMadrid(doc, 14, 8, frefor1, frefor2, frefor3);

//        % Amend Accessibility
//    % Main roads distance decay
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[1]", aramdd);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[2]", permdd);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[3]", pasmdd);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[4]", agrmdd);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[5]", resmdd);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[6]", indmdd);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[7]", recmdd);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[8]", formdd);
//     % Main roads weights
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[1]", aramwe);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[2]", permwe);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[3]", pasmwe);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[4]", agrmwe);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[5]", resmwe);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[6]", indmwe);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[7]", recmwe);
    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1990-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[8]", formwe);

    //Seed setting done in Geonamica Optimiser Core, not in plugin.
//    setAllValuesXMLNodeMadrid(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Total_potential\"]/TotalPotentialBlock/Seed", seed);


    doc.save_file(geoproj_path.c_str());
}

const std::string
MadridDVsModule::name() const
{
    return std::string("Madrid decision variables geoproj setter");
}

void
MadridDVsModule::configure(const std::string _configure_string, const boost::filesystem::path _geoproj_dir)
{
    // get paths of important files in working directory.
    // _configure_string to simply contain the path of the geoproj file relative to geoproj directory.
//    working_project = _geoproj_dir / _configure_string;
    std::vector<double> real_lower_bounds = {0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, -1000, 0.05, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<double> real_upper_bounds = {1500, 1000, 5, 1500, 1000, 5, 1500, 1000, 5, 1500, 1000, 5, 1500, 1000, 5, 1500, 1000, 5, 1500, 1000, 5, 1500, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 150, 1000, 5, 20, 20, 20, 20, 20, 20, 20, 20, 1, 1, 1, 1, 1, 1, 1, 1};

//    std::vector<double> real_lower_bounds = {0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, -100, 0.05, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0};
//    std::vector<double> real_upper_bounds = {1500, 100, 5, 1500, 100, 5, 1500, 100, 5, 1500, 100, 5, 1500, 100, 5, 1500, 100, 5, 1500, 100, 5, 1500, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 150, 100, 5, 20, 20, 20, 20, 20, 20, 20, 20, 1, 1, 1, 1, 1, 1, 1, 1};

    real_bounds.lower_bounds = real_lower_bounds;
    real_bounds.upper_bounds = real_upper_bounds;
}

void
MadridDVsModule::setDVs(const std::vector<double> &_real_decision_vars,
                        const std::vector<int> &_int_decision_vars, const boost::filesystem::path _geoproj_file) const
{
    geoprojectEditMadrid(_geoproj_file, _real_decision_vars);
}

const DVModuleAPI::Bounds<double> &
MadridDVsModule::realBounds() const
{
    return (real_bounds);
}

const DVModuleAPI::Bounds<int> &
MadridDVsModule::intBounds() const
{
    return (int_bounds);
}

extern "C" BOOST_SYMBOL_EXPORT MadridDVsModule dv_module;
MadridDVsModule dv_module;


