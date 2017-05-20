//
// Created by a1091793 on 17/11/16.
//

#ifndef CHARLES_METRO_CAL_GEOPROJECTMANIPSMALLCASESTUDY_H
#define CHARLES_METRO_CAL_GEOPROJECTMANIPSMALLCASESTUDY_H


#include <pugixml.hpp>
#include <cmath>
#include <boost/filesystem.hpp>
#include <string>

void addPointElementSmallCaseStudy(pugi::xml_node & node, int x_val, double & y_val)
{
    pugi::xml_node elmnt = node.append_child("point");
    elmnt.append_attribute("x").set_value(x_val);
    elmnt.append_attribute("y").set_value(y_val);

}

void setExpRuleSmallCaseStudy(pugi::xml_document & doc, int lu_index, int function_index, double I, double a, double b)
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
    addPointElementSmallCaseStudy(new_parent, 0, I);

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
        addPointElementSmallCaseStudy(new_parent, 1, y1);
    } else {
        addPointElementSmallCaseStudy(new_parent, 1, default_y);
    }
    if (z2 > 0.0001) {
        addPointElementSmallCaseStudy(new_parent, 2, y2);
    } else {
        addPointElementSmallCaseStudy(new_parent, 2, default_y);
    }
    if (z3 > 0.0001) {
        addPointElementSmallCaseStudy(new_parent, 3, (y3));
    } else {
        addPointElementSmallCaseStudy(new_parent, 3, default_y);
    }
    // Add
    if (z4 > 0.0001) {
        addPointElementSmallCaseStudy(new_parent, 4, (y4));
    } else {
        addPointElementSmallCaseStudy(new_parent, 4, default_y);
    }
    if (z5 > 0.0001) {
        addPointElementSmallCaseStudy(new_parent, 5, (y5));
    } else {
        addPointElementSmallCaseStudy(new_parent, 5, default_y);
    }
    if (z6 > 0.0001) {
        addPointElementSmallCaseStudy(new_parent, 6, (y6));
    } else {
        addPointElementSmallCaseStudy(new_parent, 6, default_y);
    }
    if (z7 > 0.0001) {
        addPointElementSmallCaseStudy(new_parent, 7, (y7));
    } else {
        addPointElementSmallCaseStudy(new_parent, 7, default_y);
    }
    addPointElementSmallCaseStudy(new_parent, 8, default_y);

}

template <typename T> void
setAllValuesXMLNodeSmallCaseStudy(pugi::xml_document & doc, std::string xpath_query, T new_value)
{
    pugi::xpath_node_set nodes = doc.select_nodes(xpath_query.c_str());
    for (pugi::xpath_node_set::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        pugi::xpath_node node = *it;
        node.node().first_child().set_value(std::to_string(new_value).c_str());
    }
}



void
geoprojectEditSmallCaseStudy(boost::filesystem::path & geoproj_path, const std::vector<double> & dvs, int seed)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(geoproj_path.c_str());
    //// Parameters - Self-Influence Neighbourhood Rules
    // Greenhouses (Function Class 1)
    // From GREenhouses to GREenhouses
    double gregre1 = dvs[0];
    double gregre2 = dvs[1];
    double gregre3 = dvs[2];
    // Residential (Function Class 2)
    // From Residential to Residential
    double resres1 = dvs[3];
    double resres2 = dvs[4];
    double resres3 = dvs[5];
    // Industry (Function Class 3)
    // From INDustry to INDustry
    double indind1 = dvs[6];
    double indind2 = dvs[7];
    double indind3 = dvs[8];
    // Services (Function Class 4)
    // From SERvices to SERvices
    double serser1 = dvs[9];
    double serser2 = dvs[10];
    double serser3 = dvs[11];
    // Socio cultural uses (Function class 5)
    // From Socio Cultural Uses to Socio Cultural Uses
    double scuscu1 = dvs[12];
    double scuscu2 = dvs[13];
    double scuscu3 = dvs[14];
    // Nature (Function class 6)
    // From NATure to NATure
    double natnat1 = dvs[15];
    double natnat2 = dvs[16];
    double natnat3 = dvs[17];
    // Recreation Areas (Function class 7)
    // From RECreation areas to RECreation areas
    double recrec1 = dvs[18];
    double recrec2 = dvs[19];
    double recrec3 = dvs[20];

    //// Parameters - Interaction Neighbourhood Rules
    // Greenhouses (Function Class 1)
    // From AGriculture to GREenhouses
    double agrgre1 = dvs[21];
    double agrgre2 = dvs[22];
    double agrgre3 = dvs[23];
    // From RESidential to GREenhouses
    double resgre1 = dvs[24];
    double resgre2 = dvs[25];
    double resgre3 = dvs[26];
    // From INDustry to GREenhouses
    double indgre1 = dvs[27];
    double indgre2 = dvs[28];
    double indgre3 = dvs[29];
    // From SERvices to GREenhouses
    double sergre1 = dvs[30];
    double sergre2 = dvs[31];
    double sergre3 = dvs[32];
    // From Socio Cultural Uses to GREenhouses
    double scugre1 = dvs[33];
    double scugre2 = dvs[34];
    double scugre3 = dvs[35];
    // From NATure to GREenhouses
    double natgre1 = dvs[36];
    double natgre2 = dvs[37];
    double natgre3 = dvs[38];
    // From RECreation areas to GREenhouses
    double recgre1 = dvs[39];
    double recgre2 = dvs[40];
    double recgre3 = dvs[41];
    // From AIRport to GREenhouses
    double airgre1 = dvs[42];
    double airgre2 = dvs[43];
    double airgre3 = dvs[44];
    // From WATer to GREenhouses
    double watgre1 = dvs[45];
    double watgre2 = dvs[46];
    double watgre3 = dvs[47];

    // Residential (Function Class 2)
    // From AGRiculture to RESidential
    double agrres1 = dvs[48];
    double agrres2 = dvs[49];
    double agrres3 = dvs[50];
    // From GREenhouses to RESidential
    double greres1 = dvs[51];
    double greres2 = dvs[52];
    double greres3 = dvs[53];
    // From INDustry to RESidential
    double indres1 = dvs[54];
    double indres2 = dvs[55];
    double indres3 = dvs[56];
    // From SERvices to RESidential
    double serres1 = dvs[57];
    double serres2 = dvs[58];
    double serres3 = dvs[59];
    // From Socio Cultural Uses to RESidential
    double scures1 = dvs[60];
    double scures2 = dvs[61];
    double scures3 = dvs[62];
    // From NATure to RESidential
    double natres1 = dvs[63];
    double natres2 = dvs[64];
    double natres3 = dvs[65];
    // From RECreation areas to RESidential
    double recres1 = dvs[66];
    double recres2 = dvs[67];
    double recres3 = dvs[68];
    // From AIRport to RESidential
    double airres1 = dvs[69];
    double airres2 = dvs[70];
    double airres3 = dvs[71];
    // From WATer to RESidential
    double watres1 = dvs[72];
    double watres2 = dvs[73];
    double watres3 = dvs[74];

    // Industry (Function Class 3)
    // From AGRiculture to INDustry
    double agrind1 = dvs[75];
    double agrind2 = dvs[76];
    double agrind3 = dvs[77];
    // From GREenhouses to INDustry
    double greind1 = dvs[78];
    double greind2 = dvs[79];
    double greind3 = dvs[80];
    // From RESidential to INDustry
    double resind1 = dvs[81];
    double resind2 = dvs[82];
    double resind3 = dvs[83];
    // From SERvices to INDustry
    double serind1 = dvs[84];
    double serind2 = dvs[85];
    double serind3 = dvs[86];
    // From Socio Cultural Uses to INDustry
    double scuind1 = dvs[87];
    double scuind2 = dvs[88];
    double scuind3 = dvs[89];
    // From NATure to INDustry
    double natind1 = dvs[90];
    double natind2 = dvs[91];
    double natind3 = dvs[92];
    // From RECreation areas to INDustry
    double recind1 = dvs[93];
    double recind2 = dvs[94];
    double recind3 = dvs[95];
    // From AIRport to INDustry
    double airind1 = dvs[96];
    double airind2 = dvs[97];
    double airind3 = dvs[98];
    // From WATer to INDustry
    double watind1 = dvs[99];
    double watind2 = dvs[100];
    double watind3 = dvs[101];

    // Services (Function Class 4)
    // From AGRiculture to SERvices
    double agrser1 = dvs[102];
    double agrser2 = dvs[103];
    double agrser3 = dvs[104];
    // From GREenhouses to SERvices
    double greser1 = dvs[105];
    double greser2 = dvs[106];
    double greser3 = dvs[107];
    // From RESidential to SERvices
    double resser1 = dvs[108];
    double resser2 = dvs[109];
    double resser3 = dvs[110];
    // From INDustry to SERvices
    double indser1 = dvs[111];
    double indser2 = dvs[112];
    double indser3 = dvs[113];
    // From Socio Cultural uses to SERvices
    double scuser1 = dvs[114];
    double scuser2 = dvs[115];
    double scuser3 = dvs[116];
    // From NATure to SERvices
    double natser1 = dvs[117];
    double natser2 = dvs[118];
    double natser3 = dvs[119];
    // From RECreation areas to SERvices
    double recser1 = dvs[120];
    double recser2 = dvs[121];
    double recser3 = dvs[122];
    // From AIRport to SERvices
    double airser1 = dvs[123];
    double airser2 = dvs[124];
    double airser3 = dvs[125];
    // From WATer to SERvices
    double watser1 = dvs[126];
    double watser2 = dvs[127];
    double watser3 = dvs[128];

    // Socio cultural uses (Function class 6)
    // From AGRiculture to Socio Cultural Uses
    double agrscu1 = dvs[129];
    double agrscu2 = dvs[130];
    double agrscu3 = dvs[131];
    // From GREenhouses to Socio Cultural Uses
    double grescu1 = dvs[132];
    double grescu2 = dvs[133];
    double grescu3 = dvs[134];
    // From RESidential to Socio Cultural Uses
    double resscu1 = dvs[135];
    double resscu2 = dvs[136];
    double resscu3 = dvs[137];
    // From INDustry to Socio Cultural Uses
    double indscu1 = dvs[138];
    double indscu2 = dvs[139];
    double indscu3 = dvs[140];
    // From SERvices to Socio Cultural Uses
    double serscu1 = dvs[141];
    double serscu2 = dvs[142];
    double serscu3 = dvs[143];
    // From NATure to Socio Cultural Uses
    double natscu1 = dvs[144];
    double natscu2 = dvs[145];
    double natscu3 = dvs[146];
    // From RECreation areas to Socio Cultural Uses
    double recscu1 = dvs[147];
    double recscu2 = dvs[148];
    double recscu3 = dvs[149];
    // From AIRport to Socio Cultural Uses
    double airscu1 = dvs[150];
    double airscu2 = dvs[151];
    double airscu3 = dvs[152];
    // From WATer to Socio Cultural Uses
    double watscu1 = dvs[153];
    double watscu2 = dvs[154];
    double watscu3 = dvs[155];

    // Nature (Function class 6)
    // From AGRiculture to NATure
    double agrnat1 = dvs[156];
    double agrnat2 = dvs[157];
    double agrnat3 = dvs[158];
    // From GREenhouses to NATure
    double grenat1 = dvs[159];
    double grenat2 = dvs[160];
    double grenat3 = dvs[161];
    // From RESidential to NATure
    double resnat1 = dvs[162];
    double resnat2 = dvs[163];
    double resnat3 = dvs[164];
    // From INDustry to NATure
    double indnat1 = dvs[165];
    double indnat2 = dvs[166];
    double indnat3 = dvs[167];
    // From SERvices to NATure
    double sernat1 = dvs[168];
    double sernat2 = dvs[169];
    double sernat3 = dvs[170];
    // From Socio Cultural Uses to NATure
    double scunat1 = dvs[171];
    double scunat2 = dvs[172];
    double scunat3 = dvs[173];
    // From RECreation ares to NATure
    double recnat1 = dvs[174];
    double recnat2 = dvs[175];
    double recnat3 = dvs[176];
    // From AIRport to NATure
    double airnat1 = dvs[177];
    double airnat2 = dvs[178];
    double airnat3 = dvs[179];
    // From WATer to NATure
    double watnat1 = dvs[180];
    double watnat2 = dvs[181];
    double watnat3 = dvs[182];

    // Recreation Areas (Function class 7)
    // From AGRiculture to RECreation areas
    double agrrec1 = dvs[183];
    double agrrec2 = dvs[184];
    double agrrec3 = dvs[185];
    // From GREenhouses to RECreation areas
    double grerec1 = dvs[186];
    double grerec2 = dvs[187];
    double grerec3 = dvs[188];
    // From RESidential to RECreation areas
    double resrec1 = dvs[189];
    double resrec2 = dvs[190];
    double resrec3 = dvs[191];
    // From INDustry to RECreation areas
    double indrec1 = dvs[192];
    double indrec2 = dvs[193];
    double indrec3 = dvs[194];
    // From SERvices to RECreation areas
    double serrec1 = dvs[195];
    double serrec2 = dvs[196];
    double serrec3 = dvs[197];
    // From Socio Cultural Uses to RECreation areas
    double scurec1 = dvs[198];
    double scurec2 = dvs[199];
    double scurec3 = dvs[200];
    // From NATure to RECreation areas
    double natrec1 = dvs[201];
    double natrec2 = dvs[202];
    double natrec3 = dvs[203];
    // From AIRport to RECreation areas
    double airrec1 = dvs[204];
    double airrec2 = dvs[205];
    double airrec3 = dvs[206];
    // From WATer to RECreation areas
    double watrec1 = dvs[207];
    double watrec2 = dvs[208];
    double watrec3 = dvs[209];

    //// Parameters - Accessibility distance decay
    // Greenhouses
    double gremdd = dvs[210];
    double greodd = dvs[211];
    // Residential
    double resmdd = dvs[212];
    double resodd = dvs[213];
    // Industry
    double indmdd = dvs[214];
    double indodd = dvs[215];
    // Services
    double sermdd = dvs[216];
    double serodd = dvs[217];
    // Socio cultural Uses
    double scumdd = dvs[218];
    double scuodd = dvs[219];
    // Nature
    double natmdd = dvs[220];
    double natodd = dvs[221];
    // Recreation areas
    double recmdd = dvs[222];
    double recodd = dvs[223];
    //// Parameters - Accessibility Weights
    // Greenhouses
    double gremwe = dvs[224];
    double greowe = dvs[225];
    // Residential
    double resmwe = dvs[226];
    double resowe = dvs[227];
    // Industry
    double indmwe = dvs[228];
    double indowe = dvs[229];
    // Services
    double sermwe = dvs[230];
    double serowe = dvs[231];
    // Socio cultural uses
    double scumwe = dvs[232];
    double scuowe = dvs[233];
    // Nature
    double natmwe = dvs[234];
    double natowe = dvs[235];
    // Recreation areas
    double recmwe = dvs[236];
    double recowe = dvs[237];

    // Greenhouses
    setExpRuleSmallCaseStudy(doc, 2, 1, gregre1, gregre2, gregre3);
    // Residential
    setExpRuleSmallCaseStudy(doc, 3, 2, resres1, resres2, resres3);
    // Industry
    setExpRuleSmallCaseStudy(doc, 4, 3, indind1, indind2, indind3);
    // Services
    setExpRuleSmallCaseStudy(doc, 5, 4, serser1, serser2, serser3);
    // Socio cultural uses
    setExpRuleSmallCaseStudy(doc, 6, 5, scuscu1, scuscu2, scuscu3);
    // Nature
    setExpRuleSmallCaseStudy(doc, 7, 6, natnat1, natnat2, natnat3);
    // Recreation areas
    setExpRuleSmallCaseStudy(doc, 8, 7, recrec1, recrec2, recrec3);

    // Amend Iteraction Neighbourhood Rules
    // Greenhouses
    setExpRuleSmallCaseStudy(doc, 1, 1, agrgre1, agrgre2, agrgre3);
    setExpRuleSmallCaseStudy(doc, 3, 1, resgre1, resgre2, resgre3);
    setExpRuleSmallCaseStudy(doc, 4, 1, indgre1, indgre2, indgre3);
    setExpRuleSmallCaseStudy(doc, 5, 1, sergre1, sergre2, sergre3);
    setExpRuleSmallCaseStudy(doc, 6, 1, scugre1, scugre2, scugre3);
    setExpRuleSmallCaseStudy(doc, 7, 1, natgre1, natgre2, natgre3);
    setExpRuleSmallCaseStudy(doc, 8, 1, recgre1, recgre2, recgre3);
    setExpRuleSmallCaseStudy(doc, 9, 1, airgre1, airgre2, airgre3);
    setExpRuleSmallCaseStudy(doc, 10, 1, watgre1, watgre2, watgre3);
    // Residential
    setExpRuleSmallCaseStudy(doc, 1, 2, agrres1, agrres2, agrres3);
    setExpRuleSmallCaseStudy(doc, 2, 2, greres1, greres2, greres3);
    setExpRuleSmallCaseStudy(doc, 4, 2, indres1, indres2, indres3);
    setExpRuleSmallCaseStudy(doc, 5, 2, serres1, serres2, serres3);
    setExpRuleSmallCaseStudy(doc, 6, 2, scures1, scures2, scures3);
    setExpRuleSmallCaseStudy(doc, 7, 2, natres1, natres2, natres3);
    setExpRuleSmallCaseStudy(doc, 8, 2, recres1, recres2, recres3);
    setExpRuleSmallCaseStudy(doc, 9, 2, airres1, airres2, airres3);
    setExpRuleSmallCaseStudy(doc, 10, 2, watres1, watres2, watres3);
    // Industry
    setExpRuleSmallCaseStudy(doc, 1, 3, agrind1, agrind2, agrind3);
    setExpRuleSmallCaseStudy(doc, 2, 3, greind1, greind2, greind3);
    setExpRuleSmallCaseStudy(doc, 3, 3, resind1, resind2, resind3);
    setExpRuleSmallCaseStudy(doc, 5, 3, serind1, serind2, serind3);
    setExpRuleSmallCaseStudy(doc, 6, 3, scuind1, scuind2, scuind3);
    setExpRuleSmallCaseStudy(doc, 7, 3, natind1, natind2, natind3);
    setExpRuleSmallCaseStudy(doc, 8, 3, recind1, recind2, recind3);
    setExpRuleSmallCaseStudy(doc, 9, 3, airind1, airind2, airind3);
    setExpRuleSmallCaseStudy(doc, 10, 3, watind1, watind2, watind3);
    // Services
    setExpRuleSmallCaseStudy(doc, 1, 4, agrser1, agrser2, agrser3);
    setExpRuleSmallCaseStudy(doc, 2, 4, greser1, greser2, greser3);
    setExpRuleSmallCaseStudy(doc, 3, 4, resser1, resser2, resser3);
    setExpRuleSmallCaseStudy(doc, 4, 4, indser1, indser2, indser3);
    setExpRuleSmallCaseStudy(doc, 6, 4, scuser1, scuser2, scuser3);
    setExpRuleSmallCaseStudy(doc, 7, 4, natser1, natser2, natser3);
    setExpRuleSmallCaseStudy(doc, 8, 4, recser1, recser2, recser3);
    setExpRuleSmallCaseStudy(doc, 9, 4, airser1, airser2, airser3);
    setExpRuleSmallCaseStudy(doc, 10, 4, watser1, watser2, watser3);
    // Socio cultural uses
    setExpRuleSmallCaseStudy(doc, 1, 5, agrscu1, agrscu2, agrscu3);
    setExpRuleSmallCaseStudy(doc, 2, 5, grescu1, grescu2, grescu3);
    setExpRuleSmallCaseStudy(doc, 3, 5, resscu1, resscu2, resscu3);
    setExpRuleSmallCaseStudy(doc, 4, 5, indscu1, indscu2, indscu3);
    setExpRuleSmallCaseStudy(doc, 5, 5, serscu1, serscu2, serscu3);
    setExpRuleSmallCaseStudy(doc, 7, 5, natscu1, natscu2, natscu3);
    setExpRuleSmallCaseStudy(doc, 8, 5, recscu1, recscu2, recscu3);
    setExpRuleSmallCaseStudy(doc, 9, 5, airscu1, airscu2, airscu3);
    setExpRuleSmallCaseStudy(doc, 10, 5, watscu1, watscu2, watscu3);
    // Nature
    setExpRuleSmallCaseStudy(doc, 1, 6, agrnat1, agrnat2, agrnat3);
    setExpRuleSmallCaseStudy(doc, 2, 6, grenat1, grenat2, grenat3);
    setExpRuleSmallCaseStudy(doc, 3, 6, resnat1, resnat2, resnat3);
    setExpRuleSmallCaseStudy(doc, 4, 6, indnat1, indnat2, indnat3);
    setExpRuleSmallCaseStudy(doc, 5, 6, sernat1, sernat2, sernat3);
    setExpRuleSmallCaseStudy(doc, 6, 6, scunat1, scunat2, scunat3);
    setExpRuleSmallCaseStudy(doc, 8, 6, recnat1, recnat2, recnat3);
    setExpRuleSmallCaseStudy(doc, 9, 6, airnat1, airnat2, airnat3);
    setExpRuleSmallCaseStudy(doc, 10, 6, watnat1, watnat2, watnat3);
    // Recreation areas
    setExpRuleSmallCaseStudy(doc, 1, 7, agrrec1, agrrec2, agrrec3);
    setExpRuleSmallCaseStudy(doc, 2, 7, grerec1, grerec2, grerec3);
    setExpRuleSmallCaseStudy(doc, 3, 7, resrec1, resrec2, resrec3);
    setExpRuleSmallCaseStudy(doc, 4, 7, indrec1, indrec2, indrec3);
    setExpRuleSmallCaseStudy(doc, 5, 7, serrec1, serrec2, serrec3);
    setExpRuleSmallCaseStudy(doc, 6, 7, scurec1, scurec2, scurec3);
    setExpRuleSmallCaseStudy(doc, 7, 7, natrec1, natrec2, natrec3);
    setExpRuleSmallCaseStudy(doc, 9, 7, airrec1, airrec2, airrec3);
    setExpRuleSmallCaseStudy(doc, 10, 7, watrec1, watrec2, watrec3);

//        % Amend Accessibility
//    % Motorway distance decay
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[1]", gremdd);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[2]", resmdd);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[3]", indmdd);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[4]", sermdd);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[5]", scumdd);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[6]", natmdd);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[7]", recmdd);
//        % Other roads distance decay
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[1]", greodd);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[2]", resodd);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[3]", indodd);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[4]", serodd);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[5]", scuodd);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[6]", natodd);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[7]", recodd);
//        % Motorway weights
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[1]", gremwe);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[2]", resmwe);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[3]", indmwe);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[4]", sermwe);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[5]", scumwe);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[6]", natmwe);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[7]", recmwe);
//        % Other roads weights
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[1]", greowe);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[2]", resowe);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[3]", indowe);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[4]", serowe);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[5]", scuowe);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[6]", natowe);
    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[7]", recowe);

    setAllValuesXMLNodeSmallCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Total_potential\"]/TotalPotentialBlock/Seed", seed);


    doc.save_file(geoproj_path.c_str());
}

#endif //CHARLES_METRO_CAL_GEOPROJECTMANIPSMALLCASESTUDY_H
