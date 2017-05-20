//
// Created by a1091793 on 17/11/16.
//

#ifndef CHARLES_METRO_CAL_GEOPROJECTMANIPBIGCASESTUDY_H
#define CHARLES_METRO_CAL_GEOPROJECTMANIPBIGCASESTUDY_H


#include <pugixml.hpp>
#include <cmath>
#include <boost/filesystem.hpp>
#include <string>

void addPointElementLargeCaseStudy(pugi::xml_node & node, int x_val, double & y_val)
{
    pugi::xml_node elmnt = node.append_child("point");
    elmnt.append_attribute("x").set_value(x_val);
    elmnt.append_attribute("y").set_value(y_val);

}

void setExpRuleLargeCaseStudy(pugi::xml_document & doc, int lu_index, int function_index, double I, double a, double b)
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
    addPointElementLargeCaseStudy(new_parent, 0, I);

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
        addPointElementLargeCaseStudy(new_parent, 1, y1);
    } else {
        addPointElementLargeCaseStudy(new_parent, 1, default_y);
    }
    if (z2 > 0.0001) {
        addPointElementLargeCaseStudy(new_parent, 2, y2);
    } else {
        addPointElementLargeCaseStudy(new_parent, 2, default_y);
    }
    if (z3 > 0.0001) {
        addPointElementLargeCaseStudy(new_parent, 3, (y3));
    } else {
        addPointElementLargeCaseStudy(new_parent, 3, default_y);
    }
    // Add
    if (z4 > 0.0001) {
        addPointElementLargeCaseStudy(new_parent, 4, (y4));
    } else {
        addPointElementLargeCaseStudy(new_parent, 4, default_y);
    }
    if (z5 > 0.0001) {
        addPointElementLargeCaseStudy(new_parent, 5, (y5));
    } else {
        addPointElementLargeCaseStudy(new_parent, 5, default_y);
    }
    if (z6 > 0.0001) {
        addPointElementLargeCaseStudy(new_parent, 6, (y6));
    } else {
        addPointElementLargeCaseStudy(new_parent, 6, default_y);
    }
    if (z7 > 0.0001) {
        addPointElementLargeCaseStudy(new_parent, 7, (y7));
    } else {
        addPointElementLargeCaseStudy(new_parent, 7, default_y);
    }
    addPointElementLargeCaseStudy(new_parent, 8, default_y);

}

template <typename T> void
setAllValuesXMLNodeLargeCaseStudy(pugi::xml_document & doc, std::string xpath_query, T new_value)
{
    pugi::xpath_node_set nodes = doc.select_nodes(xpath_query.c_str());
    for (pugi::xpath_node_set::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        pugi::xpath_node node = *it;
        node.node().first_child().set_value(std::to_string(new_value).c_str());
    }
}



void
geoprojectEditLargeCaseStudy(boost::filesystem::path & geoproj_path, const std::vector<double> & dvs, int seed)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(geoproj_path.c_str());
    //// Parameters - Self-Influence Neighbourhood Rules
    // Greenhouses (Function Class 1)
    // From GREenhouses to GREenhouses
    double gregre1 = dvs[0];
    double gregre2 = dvs[1];
    double gregre3 = dvs[2];
    // Housing low density (Function Class 2)
    // From Housing Low Density to Housing Low Density
    double hldhld1 = dvs[3];
    double hldhld2 = dvs[4];
    double hldhld3 = dvs[5];
	// Housing high density (Function Class 3)
	double hhdhhd1 = dvs[6];
	double hhdhhd2 = dvs[7];
	double hhdhhd3 = dvs[8];
    // Industry (Function Class 4)
    // From INDustry to INDustry
    double indind1 = dvs[9];
    double indind2 = dvs[10];
    double indind3 = dvs[11];
    // Services (Function Class 5)
    // From SERvices to SERvices
    double serser1 = dvs[12];
    double serser2 = dvs[13];
    double serser3 = dvs[14];
    // Socio cultural uses (Function class 6)
    // From Socio Cultural Uses to Socio Cultural Uses
    double scuscu1 = dvs[15];
    double scuscu2 = dvs[16];
    double scuscu3 = dvs[17];
	// Forest (Function class 7)
	// From FORest to FORest
	double forfor1 = dvs[18];
	double forfor2 = dvs[19];
	double forfor3 = dvs[20];
	// Extensive grasslands (Function class 8)
	// From EXTensive grasslands to EXTensive grasslands
	double extext1 = dvs[21];
	double extext2 = dvs[22];
	double extext3 = dvs[23];
    // Nature (Function class 9)
    // From NATure to NATure
    double natnat1 = dvs[24];
    double natnat2 = dvs[25];
    double natnat3 = dvs[26];
    // Recreation Areas (Function class 10)
    // From RECreation areas to RECreation areas
    double recrec1 = dvs[27];
    double recrec2 = dvs[28];
    double recrec3 = dvs[29];

    //// Parameters - Interaction Neighbourhood Rules
    // Greenhouses (Function Class 1)
	// From Other AGriculture to GREenhouses
	double oaggre1 = dvs[30];
	double oaggre2 = dvs[31];
	double oaggre3 = dvs[32];
	// From PAStures to GREenhouses
	double pasgre1 = dvs[33];
	double pasgre2 = dvs[34];
	double pasgre3 = dvs[35];
	// From ARAble land to GREenhouses
	double aragre1 = dvs[36];
	double aragre2 = dvs[37];
	double aragre3 = dvs[38];
    // From Housing Low Density to GREenhouses
	double hldgre1 = dvs[39];
	double hldgre2 = dvs[40];
	double hldgre3 = dvs[41];
	// From Housing High Density to GREenhouses
	double hhdgre1 = dvs[42];
	double hhdgre2 = dvs[43];
	double hhdgre3 = dvs[44];
    // From INDustry to GREenhouses
    double indgre1 = dvs[45];
    double indgre2 = dvs[46];
    double indgre3 = dvs[47];
    // From SERvices to GREenhouses
    double sergre1 = dvs[48];
    double sergre2 = dvs[49];
    double sergre3 = dvs[50];
    // From Socio Cultural Uses to GREenhouses
    double scugre1 = dvs[51];
    double scugre2 = dvs[52];
    double scugre3 = dvs[53];
	// From FORest to GREenhouses
	double forgre1 = dvs[54];
	double forgre2 = dvs[55];
	double forgre3 = dvs[56];
	// From EXTtensive grasslands to GREenhouses
	double extgre1 = dvs[57];
	double extgre2 = dvs[58];
	double extgre3 = dvs[59];
    // From NATure to GREenhouses
    double natgre1 = dvs[60];
    double natgre2 = dvs[61];
    double natgre3 = dvs[62];
    // From RECreation areas to GREenhouses
    double recgre1 = dvs[63];
    double recgre2 = dvs[64];
    double recgre3 = dvs[65];
    // From AIRport to GREenhouses
    double airgre1 = dvs[66];
    double airgre2 = dvs[67];
    double airgre3 = dvs[68];
    // From FREsh water to GREenhouses
    double fregre1 = dvs[69];
    double fregre2 = dvs[70];
    double fregre3 = dvs[71];
	// From MARine water to GREenhouses
	double margre1 = dvs[72];
	double margre2 = dvs[73];
	double margre3 = dvs[74];

    // Housing low density (Function Class 2)
    // From Other AGriculture to Housing Low Density
    double oaghld1 = dvs[75];
    double oaghld2 = dvs[76];
    double oaghld3 = dvs[77];
	// From PAStures to Housing Low Density
	double pashld1 = dvs[78];
	double pashld2 = dvs[79];
	double pashld3 = dvs[80];
	// From ARAble land to Housing Low Density
	double arahld1 = dvs[81];
	double arahld2 = dvs[82];
	double arahld3 = dvs[83];
    // From GREenhouses to Housing Low Density
    double grehld1 = dvs[84];
    double grehld2 = dvs[85];
    double grehld3 = dvs[86];
	// From Housing High Density to Housing Low Density
	double hhdhld1 = dvs[87];
	double hhdhld2 = dvs[88];
	double hhdhld3 = dvs[89];
    // From INDustry to Housing Low Density
    double indhld1 = dvs[90];
    double indhld2 = dvs[91];
    double indhld3 = dvs[92];
    // From SERvices to Housing Low Density
    double serhld1 = dvs[93];
    double serhld2 = dvs[94];
    double serhld3 = dvs[95];
    // From Socio Cultural Uses to Housing Low Density
    double scuhld1 = dvs[96];
    double scuhld2 = dvs[97];
    double scuhld3 = dvs[98];
	// From FORest to Housing Low Density
	double forhld1 = dvs[99];
	double forhld2 = dvs[100];
	double forhld3 = dvs[101];
	// From EXTensive grasslands to Housing Low Density
	double exthld1 = dvs[102];
	double exthld2 = dvs[103];
	double exthld3 = dvs[104];
    // From NATure to Housing Low Density
    double nathld1 = dvs[105];
    double nathld2 = dvs[106];
    double nathld3 = dvs[107];
    // From RECreation areas to Housing Low Density
    double rechld1 = dvs[108];
    double rechld2 = dvs[109];
    double rechld3 = dvs[110];
    // From AIRport to Housing Low Density
    double airhld1 = dvs[111];
    double airhld2 = dvs[112];
    double airhld3 = dvs[113];
    // From FREsh water to Housing Low Density
    double frehld1 = dvs[114];
    double frehld2 = dvs[115];
    double frehld3 = dvs[116];
	// From MARine water to Housing Low Density
	double marhld1 = dvs[117];
	double marhld2 = dvs[118];
	double marhld3 = dvs[119];

	// Housing high density (Function Class 3)
	// From Other AGriculture to Housing High Density
	double oaghhd1 = dvs[120];
	double oaghhd2 = dvs[121];
	double oaghhd3 = dvs[122];
	// From PAStures to Housing High Density
	double pashhd1 = dvs[123];
	double pashhd2 = dvs[124];
	double pashhd3 = dvs[125];
	// From ARAble land to Housing High Density
	double arahhd1 = dvs[126];
	double arahhd2 = dvs[127];
	double arahhd3 = dvs[128];
	// From GREenhouses to Housing High Density
	double grehhd1 = dvs[129];
	double grehhd2 = dvs[130];
	double grehhd3 = dvs[131];
	// From Housing Low Density to Housing High Density
	double hldhhd1 = dvs[132];
	double hldhhd2 = dvs[133];
	double hldhhd3 = dvs[134];
	// From INDustry to Housing High Density
	double indhhd1 = dvs[135];
	double indhhd2 = dvs[136];
	double indhhd3 = dvs[137];
	// From SERvices to Housing High Density
	double serhhd1 = dvs[138];
	double serhhd2 = dvs[139];
	double serhhd3 = dvs[140];
	// From Socio Cultural Uses to Housing High Density
	double scuhhd1 = dvs[141];
	double scuhhd2 = dvs[142];
	double scuhhd3 = dvs[143];
	// From FORest to Housing High Density
	double forhhd1 = dvs[144];
	double forhhd2 = dvs[145];
	double forhhd3 = dvs[146];
	// From EXTensive grasslands to Housing High Density
	double exthhd1 = dvs[147];
	double exthhd2 = dvs[148];
	double exthhd3 = dvs[149];
	// From NATure to Housing High Density
	double nathhd1 = dvs[150];
	double nathhd2 = dvs[151];
	double nathhd3 = dvs[152];
	// From RECreation areas to Housing High Density
	double rechhd1 = dvs[153];
	double rechhd2 = dvs[154];
	double rechhd3 = dvs[155];
	// From AIRport to Housing High Density
	double airhhd1 = dvs[156];
	double airhhd2 = dvs[157];
	double airhhd3 = dvs[158];
	// From FREsh water to Housing High Density
	double frehhd1 = dvs[159];
	double frehhd2 = dvs[160];
	double frehhd3 = dvs[161];
	// From MARine water to Housing High Density
	double marhhd1 = dvs[162];
	double marhhd2 = dvs[163];
	double marhhd3 = dvs[164];
	
    // Industry (Function Class 4)
	// From Other AGriculture to INDustry
	double oagind1 = dvs[165];
	double oagind2 = dvs[166];
	double oagind3 = dvs[167];
	// From PAStures to INDustry
	double pasind1 = dvs[168];
	double pasind2 = dvs[169];
	double pasind3 = dvs[170];
	// From ARAble land to INDustry
	double araind1 = dvs[171];
	double araind2 = dvs[172];
	double araind3 = dvs[173];
    // From GREenhouses to INDustry
    double greind1 = dvs[174];
    double greind2 = dvs[175];
    double greind3 = dvs[176];
    // From Housing Low Density to INDustry
    double hldind1 = dvs[177];
    double hldind2 = dvs[178];
    double hldind3 = dvs[179];
	// From Housing High Density to INDustry
	double hhdind1 = dvs[180];
	double hhdind2 = dvs[181];
	double hhdind3 = dvs[182];
    // From SERvices to INDustry
    double serind1 = dvs[183];
    double serind2 = dvs[184];
    double serind3 = dvs[185];
    // From Socio Cultural Uses to INDustry
    double scuind1 = dvs[186];
    double scuind2 = dvs[187];
    double scuind3 = dvs[188];
	// From FORest to INDustry
	double forind1 = dvs[189];
	double forind2 = dvs[190];
	double forind3 = dvs[191];
	// From EXTensive grasslands to INDustry
	double extind1 = dvs[192];
	double extind2 = dvs[193];
	double extind3 = dvs[194];
    // From NATure to INDustry
    double natind1 = dvs[195];
    double natind2 = dvs[196];
    double natind3 = dvs[197];
    // From RECreation areas to INDustry
    double recind1 = dvs[198];
    double recind2 = dvs[199];
    double recind3 = dvs[200];
    // From AIRport to INDustry
    double airind1 = dvs[201];
    double airind2 = dvs[202];
    double airind3 = dvs[203];
    // From FREsh water to INDustry
    double freind1 = dvs[204];
    double freind2 = dvs[205];
    double freind3 = dvs[206];
	// From MARine water to INDustry
	double marind1 = dvs[207];
	double marind2 = dvs[208];
	double marind3 = dvs[209];

    // Services (Function Class 5)
	// From Other AGriculture to SERvices
	double oagser1 = dvs[210];
	double oagser2 = dvs[211];
	double oagser3 = dvs[212];
	// From PAStures to SERvices
	double passer1 = dvs[213];
	double passer2 = dvs[214];
	double passer3 = dvs[215];
	// From ARAble land to SERvices
	double araser1 = dvs[216];
	double araser2 = dvs[217];
	double araser3 = dvs[218];
    // From GREenhouses to SERvices
    double greser1 = dvs[219];
    double greser2 = dvs[220];
    double greser3 = dvs[221];
    // From Housing Low Density to SERvices
    double hldser1 = dvs[222];
    double hldser2 = dvs[223];
    double hldser3 = dvs[224];
	// From Housing High Density to SERvices
	double hhdser1 = dvs[225];
	double hhdser2 = dvs[226];
	double hhdser3 = dvs[227];
    // From INDustry to SERvices
    double indser1 = dvs[228];
    double indser2 = dvs[229];
    double indser3 = dvs[230];
    // From Socio Cultural uses to SERvices
    double scuser1 = dvs[231];
    double scuser2 = dvs[232];
    double scuser3 = dvs[233];
	// From FORest to SERvices
	double forser1 = dvs[234];
	double forser2 = dvs[235];
	double forser3 = dvs[236];
	// From EXTensive grasslands to SERvices
	double extser1 = dvs[237];
	double extser2 = dvs[238];
	double extser3 = dvs[239];
    // From NATure to SERvices
    double natser1 = dvs[240];
    double natser2 = dvs[241];
    double natser3 = dvs[242];
    // From RECreation areas to SERvices
    double recser1 = dvs[243];
    double recser2 = dvs[244];
    double recser3 = dvs[245];
    // From AIRport to SERvices
    double airser1 = dvs[246];
    double airser2 = dvs[247];
    double airser3 = dvs[248];
    // From FREsh water to SERvices
    double freser1 = dvs[249];
    double freser2 = dvs[250];
    double freser3 = dvs[251];
	// From MARine water to SERvices
	double marser1 = dvs[252];
	double marser2 = dvs[253];
	double marser3 = dvs[254];

    // Socio cultural uses (Function class 6)
	// From Other AGriculture to Socio Cutural Uses
	double oagscu1 = dvs[255];
	double oagscu2 = dvs[256];
	double oagscu3 = dvs[257];
	// From PAStures to Socio Cultural Uses
	double passcu1 = dvs[258];
	double passcu2 = dvs[259];
	double passcu3 = dvs[260];
	// From ARAble land to Socio Cultural Uses
	double arascu1 = dvs[261];
	double arascu2 = dvs[262];
	double arascu3 = dvs[263];
    // From GREenhouses to Socio Cultural Uses
    double grescu1 = dvs[264];
    double grescu2 = dvs[265];
    double grescu3 = dvs[266];
	// From Housing Low Density to Socio Cultural Uses
	double hldscu1 = dvs[267];
	double hldscu2 = dvs[268];
	double hldscu3 = dvs[269];
	// From Housing High Density to Socio Cultural Uses
	double hhdscu1 = dvs[270];
	double hhdscu2 = dvs[271];
	double hhdscu3 = dvs[272];
    // From INDustry to Socio Cultural Uses
    double indscu1 = dvs[273];
    double indscu2 = dvs[274];
    double indscu3 = dvs[275];
    // From SERvices to Socio Cultural Uses
    double serscu1 = dvs[276];
    double serscu2 = dvs[277];
    double serscu3 = dvs[278];
	// From FORest to Socio Cultural Uses
	double forscu1 = dvs[279];
	double forscu2 = dvs[280];
	double forscu3 = dvs[281];
	// From EXTensive grasslands to Socio Cultural Uses
	double extscu1 = dvs[282];
	double extscu2 = dvs[283];
	double extscu3 = dvs[284];
    // From NATure to Socio Cultural Uses
    double natscu1 = dvs[285];
    double natscu2 = dvs[286];
    double natscu3 = dvs[287];
    // From RECreation areas to Socio Cultural Uses
    double recscu1 = dvs[288];
    double recscu2 = dvs[289];
    double recscu3 = dvs[290];
    // From AIRport to Socio Cultural Uses
    double airscu1 = dvs[291];
    double airscu2 = dvs[292];
    double airscu3 = dvs[293];
    // From FREsh water to Socio Cultural Uses
    double frescu1 = dvs[294];
    double frescu2 = dvs[295];
    double frescu3 = dvs[296];
	// From MARine water to Socio Cultural Uses
	double marscu1 = dvs[297];
	double marscu2 = dvs[298];
	double marscu3 = dvs[299];

	// Forest (Function class 7)
	// From Other AGriculture to FORest
	double oagfor1 = dvs[300];
	double oagfor2 = dvs[301];
	double oagfor3 = dvs[302];
	// From PAStures to FORest
	double pasfor1 = dvs[303];
	double pasfor2 = dvs[304];
	double pasfor3 = dvs[305];
	// From ARAble land to FORest
	double arafor1 = dvs[306];
	double arafor2 = dvs[307];
	double arafor3 = dvs[308];
	// From GREenhouses to FORest
	double grefor1 = dvs[309];
	double grefor2 = dvs[310];
	double grefor3 = dvs[311];
	// From Housing Low Density to FORest
	double hldfor1 = dvs[312];
	double hldfor2 = dvs[313];
	double hldfor3 = dvs[314];
	// From Housing High Density to FORest
	double hhdfor1 = dvs[315];
	double hhdfor2 = dvs[316];
	double hhdfor3 = dvs[317];
	// From INDusty to FORest
	double indfor1 = dvs[318];
	double indfor2 = dvs[319];
	double indfor3 = dvs[320];
	// From SERvices to FORest
	double serfor1 = dvs[321];
	double serfor2 = dvs[322];
	double serfor3 = dvs[323];
	// From Socio Cultural Uses to FORest
	double scufor1 = dvs[324];
	double scufor2 = dvs[325];
	double scufor3 = dvs[326];
	// From EXTtensive grasslands to FORest
	double extfor1 = dvs[327];
	double extfor2 = dvs[328];
	double extfor3 = dvs[329];
	// From NATure to FORest
	double natfor1 = dvs[330];
	double natfor2 = dvs[331];
	double natfor3 = dvs[332];
	// From RECreation areas to FOREst
	double recfor1 = dvs[333];
	double recfor2 = dvs[334];
	double recfor3 = dvs[335];
	// From AIRport to FORest
	double airfor1 = dvs[336];
	double airfor2 = dvs[337];
	double airfor3 = dvs[338];
	// From FREsh water to FORest
	double frefor1 = dvs[339];
	double frefor2 = dvs[340];
	double frefor3 = dvs[341];
	// From MARine water to FORest
	double marfor1 = dvs[342];
	double marfor2 = dvs[343];
	double marfor3 = dvs[344];

	// Extensive grasslands (class 8)
	// From Other AGriculture to EXTensive grasslands
	double oagext1 = dvs[345];
	double oagext2 = dvs[346];
	double oagext3 = dvs[347];
	// From PAStures to EXTensive grasslands
	double pasext1 = dvs[348];
	double pasext2 = dvs[349];
	double pasext3 = dvs[350];
	// From ARAble land to EXTensive grasslands
	double araext1 = dvs[351];
	double araext2 = dvs[352];
	double araext3 = dvs[353];
	// From GREenhouses to EXTensive grasslands
	double greext1 = dvs[354];
	double greext2 = dvs[355];
	double greext3 = dvs[356];
	// From Housing Low Density to EXTensive grasslands
	double hldext1 = dvs[357];
	double hldext2 = dvs[358];
	double hldext3 = dvs[359];
	// From Housing High Density to EXTensive grasslands
	double hhdext1 = dvs[360];
	double hhdext2 = dvs[361];
	double hhdext3 = dvs[362];
	// From INDusty to EXTensive grasslands
	double indext1 = dvs[363];
	double indext2 = dvs[364];
	double indext3 = dvs[365];
	// From SERvices to EXTensive grasslands
	double serext1 = dvs[366];
	double serext2 = dvs[367];
	double serext3 = dvs[368];
	// From Socio Cultural Uses to EXTensive grasslands
	double scuext1 = dvs[369];
	double scuext2 = dvs[370];
	double scuext3 = dvs[371];
	// From FORest to EXTensive grasslands
	double forext1 = dvs[372];
	double forext2 = dvs[373];
	double forext3 = dvs[374];
	// From NATure to EXTensive grasslands
	double natext1 = dvs[375];
	double natext2 = dvs[376];
	double natext3 = dvs[377];
	// From RECreation areas to EXTensive grasslands
	double recext1 = dvs[378];
	double recext2 = dvs[379];
	double recext3 = dvs[380];
	// From AIRport to EXTensive grasslands
	double airext1 = dvs[381];
	double airext2 = dvs[382];
	double airext3 = dvs[383];
	// From FREsh water to EXTensive grasslands
	double freext1 = dvs[384];
	double freext2 = dvs[385];
	double freext3 = dvs[386];
	// From MARine water to EXTensive grasslands
	double marext1 = dvs[387];
	double marext2 = dvs[388];
	double marext3 = dvs[389];
	
    // Nature (Function class 9)
	// From Other AGriculture to NATure
	double oagnat1 = dvs[390];
	double oagnat2 = dvs[391];
	double oagnat3 = dvs[392];
	// From PAStures to NATure
	double pasnat1 = dvs[393];
	double pasnat2 = dvs[394];
	double pasnat3 = dvs[395];
	// From ARAble land to NATure
	double aranat1 = dvs[396];
	double aranat2 = dvs[397];
	double aranat3 = dvs[398];
    // From GREenhouses to NATure
    double grenat1 = dvs[399];
    double grenat2 = dvs[400];
    double grenat3 = dvs[401];
	// From Housing Low Density to NATure
	double hldnat1 = dvs[402];
	double hldnat2 = dvs[403];
	double hldnat3 = dvs[404];
	// From Housing High Density to Nature
	double hhdnat1 = dvs[405];
	double hhdnat2 = dvs[406];
	double hhdnat3 = dvs[407];
    // From INDustry to NATure
    double indnat1 = dvs[408];
    double indnat2 = dvs[409];
    double indnat3 = dvs[410];
    // From SERvices to NATure
    double sernat1 = dvs[411];
    double sernat2 = dvs[412];
    double sernat3 = dvs[413];
    // From Socio Cultural Uses to NATure
    double scunat1 = dvs[414];
    double scunat2 = dvs[415];
    double scunat3 = dvs[416];
	// From FORest to NATure
	double fornat1 = dvs[417];
	double fornat2 = dvs[418];
	double fornat3 = dvs[419];
	// From EXTensive grasslands to NATure
	double extnat1 = dvs[420];
	double extnat2 = dvs[421];
	double extnat3 = dvs[422];
    // From RECreation ares to NATure
    double recnat1 = dvs[423];
    double recnat2 = dvs[424];
    double recnat3 = dvs[425];
    // From AIRport to NATure
    double airnat1 = dvs[426];
    double airnat2 = dvs[427];
    double airnat3 = dvs[428];
    // From FREsh water to NATure
    double frenat1 = dvs[429];
    double frenat2 = dvs[430];
    double frenat3 = dvs[431];
	// From MARine water to NATure 
	double marnat1 = dvs[432];
	double marnat2 = dvs[433];
	double marnat3 = dvs[434];

    // Recreation Areas (Function class 10)
	// From Other AGricluture to RECreation areas
	double oagrec1 = dvs[435];
	double oagrec2 = dvs[436];
	double oagrec3 = dvs[437];
	// From PAStures to RECreation areas
	double pasrec1 = dvs[438];
	double pasrec2 = dvs[439];
	double pasrec3 = dvs[440];
	// From ARAble land to RECreation areas
	double ararec1 = dvs[441];
	double ararec2 = dvs[442];
	double ararec3 = dvs[443];
    // From GREenhouses to RECreation areas
    double grerec1 = dvs[444];
    double grerec2 = dvs[445];
    double grerec3 = dvs[446];
	// From Housing Low Density to RECreation areas
	double hldrec1 = dvs[447];
	double hldrec2 = dvs[448];
	double hldrec3 = dvs[449];
	// From Housing High Density to RECreation areas
	double hhdrec1 = dvs[450];
	double hhdrec2 = dvs[451];
	double hhdrec3 = dvs[452];
    // From INDustry to RECreation areas
    double indrec1 = dvs[453];
    double indrec2 = dvs[454];
    double indrec3 = dvs[455];
    // From SERvices to RECreation areas
    double serrec1 = dvs[456];
    double serrec2 = dvs[457];
    double serrec3 = dvs[458];
    // From Socio Cultural Uses to RECreation areas
    double scurec1 = dvs[459];
    double scurec2 = dvs[460];
    double scurec3 = dvs[461];
	// From FORest to RECreation areas
	double forrec1 = dvs[462];
	double forrec2 = dvs[463];
	double forrec3 = dvs[464];
	// From EXTensive grasslands to RECreation areas
	double extrec1 = dvs[465];
	double extrec2 = dvs[466];
	double extrec3 = dvs[467];
    // From NATure to RECreation areas
    double natrec1 = dvs[468];
    double natrec2 = dvs[469];
    double natrec3 = dvs[470];
    // From AIRport to RECreation areas
    double airrec1 = dvs[471];
    double airrec2 = dvs[472];
    double airrec3 = dvs[473];
    // From FREsh water to RECreation areas
    double frerec1 = dvs[474];
    double frerec2 = dvs[475];
    double frerec3 = dvs[476];
	// From MARine water to RECreation areas
	double marrec1 = dvs[477];
	double marrec2 = dvs[478];
	double marrec3 = dvs[479];

    //// Parameters - Accessibility distance decay
    // Greenhouses
    double gremdd = dvs[480];
    double greodd = dvs[481];
	// Housing low density
	double hldmdd = dvs[482];
	double hldodd = dvs[483];
	// Housing high density
	double hhdmdd = dvs[484];
	double hhdodd = dvs[485];
    // Industry
    double indmdd = dvs[486];
    double indodd = dvs[487];
    // Services
    double sermdd = dvs[488];
    double serodd = dvs[489];
    // Socio cultural Uses
    double scumdd = dvs[490];
    double scuodd = dvs[491];
	// Forest
	double formdd = dvs[492];
	double forodd = dvs[493];
	// Extensive grasslands
	double extmdd = dvs[494];
	double extodd = dvs[495];
    // Nature
    double natmdd = dvs[496];
    double natodd = dvs[497];
    // Recreation areas
    double recmdd = dvs[498];
    double recodd = dvs[499];
    //// Parameters - Accessibility Weights
    // Greenhouses
    double gremwe = dvs[500];
    double greowe = dvs[501];
	// Housing low density
	double hldmwe = dvs[502];
	double hldowe = dvs[503];
	// Housing high density
	double hhdmwe = dvs[504];
	double hhdowe = dvs[505];
    // Industry
    double indmwe = dvs[506];
    double indowe = dvs[507];
    // Services
    double sermwe = dvs[508];
    double serowe = dvs[509];
    // Socio cultural uses
    double scumwe = dvs[510];
    double scuowe = dvs[511];
	// Forest
	double formwe = dvs[512];
	double forowe = dvs[513];
	// Extensive grasslands
	double extmwe = dvs[514];
	double extowe = dvs[515];
    // Nature
    double natmwe = dvs[516];
    double natowe = dvs[517];
    // Recreation areas
    double recmwe = dvs[518];
    double recowe = dvs[519];

	//	%Amend Self-influence Neighbourhood Rules
    // Greenhouses
    setExpRuleLargeCaseStudy(doc, 4, 1, gregre1, gregre2, gregre3);
	// Housing low density
	setExpRuleLargeCaseStudy(doc, 5, 2, hldhld1, hldhld2, hldhld3);
	// Housing high density
	setExpRuleLargeCaseStudy(doc, 6, 3, hhdhhd1, hhdhhd2, hhdhhd3);
    // Industry
    setExpRuleLargeCaseStudy(doc, 7, 4, indind1, indind2, indind3);
    // Services
    setExpRuleLargeCaseStudy(doc, 8, 5, serser1, serser2, serser3);
    // Socio cultural uses
    setExpRuleLargeCaseStudy(doc, 9, 6, scuscu1, scuscu2, scuscu3);
	// Forest
	setExpRuleLargeCaseStudy(doc, 10, 7, forfor1, forfor2, forfor3);
	// Extensive grasslands
	setExpRuleLargeCaseStudy(doc, 11, 8, extext1, extext2, extext3);
	    // Nature
    setExpRuleLargeCaseStudy(doc, 12, 9, natnat1, natnat2, natnat3);
    // Recreation areas
    setExpRuleLargeCaseStudy(doc, 13, 10, recrec1, recrec2, recrec3);

    //	%Amend Iteraction Neighbourhood Rules
    // Greenhouses
	setExpRuleLargeCaseStudy(doc, 1, 1, oaggre1, oaggre2, oaggre3);
	setExpRuleLargeCaseStudy(doc, 2, 1, pasgre1, pasgre2, pasgre3);
	setExpRuleLargeCaseStudy(doc, 3, 1, aragre1, aragre2, aragre3);
	setExpRuleLargeCaseStudy(doc, 5, 1, hldgre1, hldgre2, hldgre3);
	setExpRuleLargeCaseStudy(doc, 6, 1, hhdgre1, hhdgre2, hhdgre3);
    setExpRuleLargeCaseStudy(doc, 7, 1, indgre1, indgre2, indgre3);
    setExpRuleLargeCaseStudy(doc, 8, 1, sergre1, sergre2, sergre3);
    setExpRuleLargeCaseStudy(doc, 9, 1, scugre1, scugre2, scugre3);
	setExpRuleLargeCaseStudy(doc, 10, 1, forgre1, forgre2, forgre3);
	setExpRuleLargeCaseStudy(doc, 11, 1, extgre1, extgre2, extgre3);
    setExpRuleLargeCaseStudy(doc, 12, 1, natgre1, natgre2, natgre3);
    setExpRuleLargeCaseStudy(doc, 13, 1, recgre1, recgre2, recgre3);
    setExpRuleLargeCaseStudy(doc, 14, 1, airgre1, airgre2, airgre3);
    setExpRuleLargeCaseStudy(doc, 15, 1, fregre1, fregre2, fregre3);
	setExpRuleLargeCaseStudy(doc, 16, 1, margre1, margre2, margre3);
	// Housing low density
	setExpRuleLargeCaseStudy(doc, 1, 2, oaghld1, oaghld2, oaghld3);
	setExpRuleLargeCaseStudy(doc, 2, 2, pashld1, pashld2, pashld3);
	setExpRuleLargeCaseStudy(doc, 3, 2, arahld1, arahld2, arahld3);
	setExpRuleLargeCaseStudy(doc, 4, 2, grehld1, grehld2, grehld3);
	setExpRuleLargeCaseStudy(doc, 6, 2, hhdhld1, hhdhld2, hhdhld3);
	setExpRuleLargeCaseStudy(doc, 7, 2, indhld1, indhld2, indhld3);
	setExpRuleLargeCaseStudy(doc, 8, 2, serhld1, serhld2, serhld3);
	setExpRuleLargeCaseStudy(doc, 9, 2, scuhld1, scuhld2, scuhld3);
	setExpRuleLargeCaseStudy(doc, 10, 2, forhld1, forhld2, forhld3);
	setExpRuleLargeCaseStudy(doc, 11, 2, exthld1, exthld2, exthld3);
	setExpRuleLargeCaseStudy(doc, 12, 2, nathld1, nathld2, nathld3);
	setExpRuleLargeCaseStudy(doc, 13, 2, rechld1, rechld2, rechld3);
	setExpRuleLargeCaseStudy(doc, 14, 2, airhld1, airhld2, airhld3);
	setExpRuleLargeCaseStudy(doc, 15, 2, frehld1, frehld2, frehld3);
	setExpRuleLargeCaseStudy(doc, 16, 2, marhld1, marhld2, marhld3);
	// Housing high density
	setExpRuleLargeCaseStudy(doc, 1, 3, oaghhd1, oaghhd2, oaghhd3);
	setExpRuleLargeCaseStudy(doc, 2, 3, pashhd1, pashhd2, pashhd3);
	setExpRuleLargeCaseStudy(doc, 3, 3, arahhd1, arahhd2, arahhd3);
	setExpRuleLargeCaseStudy(doc, 4, 3, grehhd1, grehhd2, grehhd3);
	setExpRuleLargeCaseStudy(doc, 5, 3, hldhhd1, hldhhd2, hldhhd3);
	setExpRuleLargeCaseStudy(doc, 7, 3, indhhd1, indhhd2, indhhd3);
	setExpRuleLargeCaseStudy(doc, 8, 3, serhhd1, serhhd2, serhhd3);
	setExpRuleLargeCaseStudy(doc, 9, 3, scuhhd1, scuhhd2, scuhhd3);
	setExpRuleLargeCaseStudy(doc, 10, 3, forhhd1, forhhd2, forhhd3);
	setExpRuleLargeCaseStudy(doc, 11, 3, exthhd1, exthhd2, exthhd3);
	setExpRuleLargeCaseStudy(doc, 12, 3, nathhd1, nathhd2, nathhd3);
	setExpRuleLargeCaseStudy(doc, 13, 3, rechhd1, rechhd2, rechhd3);
	setExpRuleLargeCaseStudy(doc, 14, 3, airhhd1, airhhd2, airhhd3);
	setExpRuleLargeCaseStudy(doc, 15, 3, frehhd1, frehhd2, frehhd3);
	setExpRuleLargeCaseStudy(doc, 16, 3, marhhd1, marhhd2, marhhd3);
	// Industry
	setExpRuleLargeCaseStudy(doc, 1, 4, oagind1, oagind2, oagind3);
	setExpRuleLargeCaseStudy(doc, 2, 4, pasind1, pasind2, pasind3);
	setExpRuleLargeCaseStudy(doc, 3, 4, araind1, araind2, araind3);
	setExpRuleLargeCaseStudy(doc, 4, 4, greind1, greind2, greind3);
	setExpRuleLargeCaseStudy(doc, 5, 4, hldind1, hldind2, hldind3);
	setExpRuleLargeCaseStudy(doc, 6, 4, hhdind1, hhdind2, hhdind3);
	setExpRuleLargeCaseStudy(doc, 8, 4, serind1, serind2, serind3);
	setExpRuleLargeCaseStudy(doc, 9, 4, scuind1, scuind2, scuind3);
	setExpRuleLargeCaseStudy(doc, 10, 4, forind1, forind2, forind3);
	setExpRuleLargeCaseStudy(doc, 11, 4, extind1, extind2, extind3);
	setExpRuleLargeCaseStudy(doc, 12, 4, natind1, natind2, natind3);
	setExpRuleLargeCaseStudy(doc, 13, 4, recind1, recind2, recind3);
	setExpRuleLargeCaseStudy(doc, 14, 4, airind1, airind2, airind3);
	setExpRuleLargeCaseStudy(doc, 15, 4, freind1, freind2, freind3);
	setExpRuleLargeCaseStudy(doc, 16, 4, marind1, marind2, marind3);
	// Services
	setExpRuleLargeCaseStudy(doc, 1, 5, oagser1, oagser2, oagser3);
	setExpRuleLargeCaseStudy(doc, 2, 5, passer1, passer2, passer3);
	setExpRuleLargeCaseStudy(doc, 3, 5, araser1, araser2, araser3);
	setExpRuleLargeCaseStudy(doc, 4, 5, greser1, greser2, greser3);
	setExpRuleLargeCaseStudy(doc, 5, 5, hldser1, hldser2, hldser3);
	setExpRuleLargeCaseStudy(doc, 6, 5, hhdser1, hhdser2, hhdser3);
	setExpRuleLargeCaseStudy(doc, 7, 5, indser1, indser2, indser3);
	setExpRuleLargeCaseStudy(doc, 9, 5, scuser1, scuser2, scuser3);
	setExpRuleLargeCaseStudy(doc, 10, 5, forser1, forser2, forser3);
	setExpRuleLargeCaseStudy(doc, 11, 5, extser1, extser2, extser3);
	setExpRuleLargeCaseStudy(doc, 12, 5, natser1, natser2, natser3);
	setExpRuleLargeCaseStudy(doc, 13, 5, recser1, recser2, recser3);
	setExpRuleLargeCaseStudy(doc, 14, 5, airser1, airser2, airser3);
	setExpRuleLargeCaseStudy(doc, 15, 5, freser1, freser2, freser3);
	setExpRuleLargeCaseStudy(doc, 16, 5, marser1, marser2, marser3);
	// Socio cultural uses
	setExpRuleLargeCaseStudy(doc, 1, 6, oagscu1, oagscu2, oagscu3);
	setExpRuleLargeCaseStudy(doc, 2, 6, passcu1, passcu2, passcu3);
	setExpRuleLargeCaseStudy(doc, 3, 6, arascu1, arascu2, arascu3);
	setExpRuleLargeCaseStudy(doc, 4, 6, grescu1, grescu2, grescu3);
	setExpRuleLargeCaseStudy(doc, 5, 6, hldscu1, hldscu2, hldscu3);
	setExpRuleLargeCaseStudy(doc, 6, 6, hhdscu1, hhdscu2, hhdscu3);
	setExpRuleLargeCaseStudy(doc, 7, 6, indscu1, indscu2, indscu3);
	setExpRuleLargeCaseStudy(doc, 8, 6, serscu1, serscu2, serscu3);
	setExpRuleLargeCaseStudy(doc, 10, 6, forscu1, forscu2, forscu3);
	setExpRuleLargeCaseStudy(doc, 11, 6, extscu1, extscu2, extscu3);
	setExpRuleLargeCaseStudy(doc, 12, 6, natscu1, natscu2, natscu3);
	setExpRuleLargeCaseStudy(doc, 13, 6, recscu1, recscu2, recscu3);
	setExpRuleLargeCaseStudy(doc, 14, 6, airscu1, airscu2, airscu3);
	setExpRuleLargeCaseStudy(doc, 15, 6, frescu1, frescu2, frescu3);
	setExpRuleLargeCaseStudy(doc, 16, 6, marscu1, marscu2, marscu3);
	// Forest
	setExpRuleLargeCaseStudy(doc, 1, 7, oagfor1, oagfor2, oagfor3);
	setExpRuleLargeCaseStudy(doc, 2, 7, pasfor1, pasfor2, pasfor3);
	setExpRuleLargeCaseStudy(doc, 3, 7, arafor1, arafor2, arafor3);
	setExpRuleLargeCaseStudy(doc, 4, 7, grefor1, grefor2, grefor3);
	setExpRuleLargeCaseStudy(doc, 5, 7, hldfor1, hldfor2, hldfor3);
	setExpRuleLargeCaseStudy(doc, 6, 7, hhdfor1, hhdfor2, hhdfor3);
	setExpRuleLargeCaseStudy(doc, 7, 7, indfor1, indfor2, indfor3);
	setExpRuleLargeCaseStudy(doc, 8, 7, serfor1, serfor2, serfor3);
	setExpRuleLargeCaseStudy(doc, 9, 7, scufor1, scufor2, scufor3);
	setExpRuleLargeCaseStudy(doc, 11, 7, extfor1, extfor2, extfor3);
	setExpRuleLargeCaseStudy(doc, 12, 7, natfor1, natfor2, natfor3);
	setExpRuleLargeCaseStudy(doc, 13, 7, recfor1, recfor2, recfor3);
	setExpRuleLargeCaseStudy(doc, 14, 7, airfor1, airfor2, airfor3);
	setExpRuleLargeCaseStudy(doc, 15, 7, frefor1, frefor2, frefor3);
	setExpRuleLargeCaseStudy(doc, 16, 7, marfor1, marfor2, marfor3);
	// Extensive grasslands
	setExpRuleLargeCaseStudy(doc, 1, 8, oagext1, oagext2, oagext3);
	setExpRuleLargeCaseStudy(doc, 2, 8, pasext1, pasext2, pasext3);
	setExpRuleLargeCaseStudy(doc, 3, 8, araext1, araext2, araext3);
	setExpRuleLargeCaseStudy(doc, 4, 8, greext1, greext2, greext3);
	setExpRuleLargeCaseStudy(doc, 5, 8, hldext1, hldext2, hldext3);
	setExpRuleLargeCaseStudy(doc, 6, 8, hhdext1, hhdext2, hhdext3);
	setExpRuleLargeCaseStudy(doc, 7, 8, indext1, indext2, indext3);
	setExpRuleLargeCaseStudy(doc, 8, 8, serext1, serext2, serext3);
	setExpRuleLargeCaseStudy(doc, 9, 8, scuext1, scuext2, scuext3);
	setExpRuleLargeCaseStudy(doc, 10, 8, forext1, forext2, forext3);
	setExpRuleLargeCaseStudy(doc, 12, 8, natext1, natext2, natext3);
	setExpRuleLargeCaseStudy(doc, 13, 8, recext1, recext2, recext3);
	setExpRuleLargeCaseStudy(doc, 14, 8, airext1, airext2, airext3);
	setExpRuleLargeCaseStudy(doc, 15, 8, freext1, freext2, freext3);
	setExpRuleLargeCaseStudy(doc, 16, 8, marext1, marext2, marext3);
	// Nature
	setExpRuleLargeCaseStudy(doc, 1, 9, oagnat1, oagnat2, oagnat3);
	setExpRuleLargeCaseStudy(doc, 2, 9, pasnat1, pasnat2, pasnat3);
	setExpRuleLargeCaseStudy(doc, 3, 9, aranat1, aranat2, aranat3);
	setExpRuleLargeCaseStudy(doc, 4, 9, grenat1, grenat2, grenat3);
	setExpRuleLargeCaseStudy(doc, 5, 9, hldnat1, hldnat2, hldnat3);
	setExpRuleLargeCaseStudy(doc, 6, 9, hhdnat1, hhdnat2, hhdnat3);
	setExpRuleLargeCaseStudy(doc, 7, 9, indnat1, indnat2, indnat3);
	setExpRuleLargeCaseStudy(doc, 8, 9, sernat1, sernat2, sernat3);
	setExpRuleLargeCaseStudy(doc, 9, 9, scunat1, scunat2, scunat3);
	setExpRuleLargeCaseStudy(doc, 10, 9, fornat1, fornat2, fornat3);
	setExpRuleLargeCaseStudy(doc, 11, 9, extnat1, extnat2, extnat3);
	setExpRuleLargeCaseStudy(doc, 13, 9, recnat1, recnat2, recnat3);
	setExpRuleLargeCaseStudy(doc, 14, 9, airnat1, airnat2, airnat3);
	setExpRuleLargeCaseStudy(doc, 15, 9, frenat1, frenat2, frenat3);
	setExpRuleLargeCaseStudy(doc, 16, 9, marnat1, marnat2, marnat3);
	// Recreation areas
	setExpRuleLargeCaseStudy(doc, 1, 10, oagrec1, oagrec2, oagrec3);
	setExpRuleLargeCaseStudy(doc, 2, 10, pasrec1, pasrec2, pasrec3);
	setExpRuleLargeCaseStudy(doc, 3, 10, ararec1, ararec2, ararec3);
	setExpRuleLargeCaseStudy(doc, 4, 10, grerec1, grerec2, grerec3);
	setExpRuleLargeCaseStudy(doc, 5, 10, hldrec1, hldrec2, hldrec3);
	setExpRuleLargeCaseStudy(doc, 6, 10, hhdrec1, hhdrec2, hhdrec3);
	setExpRuleLargeCaseStudy(doc, 7, 10, indrec1, indrec2, indrec3);
	setExpRuleLargeCaseStudy(doc, 8, 10, serrec1, serrec2, serrec3);
	setExpRuleLargeCaseStudy(doc, 9, 10, scurec1, scurec2, scurec3);
	setExpRuleLargeCaseStudy(doc, 10, 10, forrec1, forrec2, forrec3);
	setExpRuleLargeCaseStudy(doc, 11, 10, extrec1, extrec2, extrec3);
	setExpRuleLargeCaseStudy(doc, 12, 10, natrec1, natrec2, natrec3);
	setExpRuleLargeCaseStudy(doc, 14, 10, airrec1, airrec2, airrec3);
	setExpRuleLargeCaseStudy(doc, 15, 10, frerec1, frerec2, frerec3);
	setExpRuleLargeCaseStudy(doc, 16, 10, marrec1, marrec2, marrec3);   

//        % Amend Accessibility
//    % Motorway distance decay
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[1]", gremdd);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[2]", hldmdd);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[3]", hhdmdd);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[4]", indmdd);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[5]", sermdd);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[6]", scumdd);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[7]", formdd);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[8]", extmdd);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[9]", natmdd);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[10]", recmdd);
//        % Other roads distance decay
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[1]", greodd);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[2]", hldodd);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[3]", hhdodd);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[4]", indodd);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[5]", serodd);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[6]", scuodd);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[7]", forodd);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[8]", extodd);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[9]", natodd);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[10]", recodd);
//        % Motorway weights
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[1]", gremwe);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[2]", hldmwe);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[3]", hhdmwe);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[4]", indmwe);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[5]", sermwe);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[6]", scumwe);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[7]", formwe);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[8]", extmwe);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[9]", natmwe);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[10]", recmwe);
//        % Other roads weights
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[1]", greowe);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[2]", hldowe);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[3]", hhdowe);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[4]", indowe);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[5]", serowe);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[6]", scuowe);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[7]", forowe);
	setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[8]", extowe);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[9]", natowe);
    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[10]", recowe);

    setAllValuesXMLNodeLargeCaseStudy(doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Total_potential\"]/TotalPotentialBlock/Seed", seed);


    doc.save_file(geoproj_path.c_str());
}

#endif //CHARLES_METRO_CAL_GEOPROJECTMANIPBIGCASESTUDY_H
