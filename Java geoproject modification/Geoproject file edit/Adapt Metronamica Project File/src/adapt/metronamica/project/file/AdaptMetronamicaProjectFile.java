/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package adapt.metronamica.project.file;



// Use Java's Xpath to manipulate XML files.
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import static java.lang.Math.abs;
import static java.lang.Math.exp;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.w3c.dom.Document;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.xpath.*;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;


/**
 *
 * @author a1091793
 */
public class AdaptMetronamicaProjectFile
{
    
    
    
    static void add_point_element(Document doc, Node nde, String x_val, String y_val)
    {
        Element elmnt = doc.createElement("point");
        elmnt.setAttribute("x", x_val);
        elmnt.setAttribute("y", y_val);
        nde.appendChild(elmnt);
        
    }
    
    static void set_exp_rule_selfinfluence(XPathFactory xPathFactory, Document doc, int lu_index, int function_index, double I, double a, double b)
    {
        try
        {
            // TODO code application logic here
            
            XPath xpath = xPathFactory.newXPath();
            String xpath_query = "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@name=\"MB_Rules\"]/RulesBlock/Rules/value/vector/elem[" + function_index + "]/vector/elem[" + lu_index + "]/spline";
            XPathExpression expr = xpath.compile(xpath_query);
            NodeList nl = (NodeList) expr.evaluate(doc, XPathConstants.NODESET);
            Node parentNode = nl.item(0).getParentNode();
            for(int i=0; i<nl.getLength() ; i++) 
            {
                parentNode.removeChild(nl.item(i));
            }
            Node new_parent = doc.createElement("spline");
            add_point_element(doc, new_parent, "0", Double.toString(I));
            
//            // Calculate exponential decay values
            double y1=a*exp(-b*1);
            double y2=a*exp(-b*2);
            double y3=a*exp(-b*3);
            double y4=a*exp(-b*4);
            double y5=a*exp(-b*5);
            double y6=a*exp(-b*6);
            double y7=a*exp(-b*7);
            // double //y8=a*exp(-b*8);
            // Calculate absolute values of exponential decay
            double z1=abs(y1);
            double z2=abs(y2);
            double z3=abs(y3);
            double z4=abs(y4);
            double z5=abs(y5);
            double z6=abs(y6);
            double z7=abs(y7);
            
            if (z1 > 0.0001)
            {
                add_point_element(doc, new_parent, "1", Double.toString(y1));
            }
            else
            {
                add_point_element(doc, new_parent, "1", "0");
            }
            if (z2 > 0.0001)
            {
                add_point_element(doc, new_parent, "2", Double.toString(y2));
            }
            else
            {
                add_point_element(doc, new_parent, "2", "0");
            }
            if (z3 > 0.0001)
            {
                add_point_element(doc, new_parent, "3", Double.toString(y3));
            }
            else
            {
                add_point_element(doc, new_parent, "3", "0");
            }
            // Add 
            if (z4 > 0.0001)
            {
                add_point_element(doc, new_parent, "4", Double.toString(y4));
            }
            else
            {
                add_point_element(doc, new_parent, "4", "0");
            }
            if (z5 > 0.0001)
            {
                add_point_element(doc, new_parent, "5", Double.toString(y5));
            }
            else
            {
                add_point_element(doc, new_parent, "5", "0");
            }
            if (z6 > 0.0001)
            {
                add_point_element(doc, new_parent, "6", Double.toString(y6));
            }
            else
            {
                add_point_element(doc, new_parent, "6", "0");
            }
            if (z7 > 0.0001)
            {
                add_point_element(doc, new_parent, "7", Double.toString(y7));
            }
            else
            {
                add_point_element(doc, new_parent, "7", "0");
            }
            add_point_element(doc, new_parent, "8", "0");
            parentNode.appendChild(new_parent);
            
        } catch (XPathExpressionException ex)
        {
            Logger.getLogger(AdaptMetronamicaProjectFile.class.getName()).log(Level.SEVERE, null, ex);
        }
            
    }
    
    static void set_exp_rule_interaction(XPathFactory xPathFactory, Document doc, int lu_index, int function_index, double a, double b)
    {
        try
        {

            XPath xpath = xPathFactory.newXPath();
            String xpath_query = "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@name=\"MB_Rules\"]/RulesBlock/Rules/value/vector/elem[" + function_index + "]/vector/elem[" + lu_index + "]/spline";
            XPathExpression expr = xpath.compile(xpath_query);
            NodeList nl = (NodeList) expr.evaluate(doc, XPathConstants.NODESET);
            Node parentNode = nl.item(0).getParentNode();
            for(int i=0; i<nl.getLength() ; i++) 
            {
                parentNode.removeChild(nl.item(i));
            }
            Node new_parent = doc.createElement("spline");
            add_point_element(doc, new_parent, "0", "0");
            
//            // Calculate exponential decay values
            double y1=a*exp(-b*1);
            double y2=a*exp(-b*2);
            double y3=a*exp(-b*3);
            double y4=a*exp(-b*4);
            double y5=a*exp(-b*5);
            double y6=a*exp(-b*6);
            double y7=a*exp(-b*7);
            // double //y8=a*exp(-b*8);
            // Calculate absolute values of exponential decay
            double z1=abs(y1);
            double z2=abs(y2);
            double z3=abs(y3);
            double z4=abs(y4);
            double z5=abs(y5);
            double z6=abs(y6);
            double z7=abs(y7);
            
            if (z1 > 0.0001)
            {
                add_point_element(doc, new_parent, "1", Double.toString(y1));
            }
            else
            {
                add_point_element(doc, new_parent, "1", "0");
            }
            if (z2 > 0.0001)
            {
                add_point_element(doc, new_parent, "2", Double.toString(y2));
            }
            else
            {
                add_point_element(doc, new_parent, "2", "0");
            }
            if (z3 > 0.0001)
            {
                add_point_element(doc, new_parent, "3", Double.toString(y3));
            }
            else
            {
                add_point_element(doc, new_parent, "3", "0");
            }
            // Add 
            if (z4 > 0.0001)
            {
                add_point_element(doc, new_parent, "4", Double.toString(y4));
            }
            else
            {
                add_point_element(doc, new_parent, "4", "0");
            }
            if (z5 > 0.0001)
            {
                add_point_element(doc, new_parent, "5", Double.toString(y5));
            }
            else
            {
                add_point_element(doc, new_parent, "5", "0");
            }
            if (z6 > 0.0001)
            {
                add_point_element(doc, new_parent, "6", Double.toString(y6));
            }
            else
            {
                add_point_element(doc, new_parent, "6", "0");
            }
            if (z7 > 0.0001)
            {
                add_point_element(doc, new_parent, "7", Double.toString(y7));
            }
            else
            {
                add_point_element(doc, new_parent, "7", "0");
            }
            add_point_element(doc, new_parent, "8", "0");
            parentNode.appendChild(new_parent);
            
        } catch (XPathExpressionException ex)
        {
            Logger.getLogger(AdaptMetronamicaProjectFile.class.getName()).log(Level.SEVERE, null, ex);
        }
            
    }

    static void set_all_values(XPathFactory xPathFactory, Document doc, String xpath_query, double new_value)
    {
        try
        {
            // TODO code application logic here
            
            XPath xpath = xPathFactory.newXPath();
            XPathExpression expr = xpath.compile(xpath_query);
            NodeList nl = (NodeList) expr.evaluate(doc, XPathConstants.NODESET);
            for(int i=0; i<nl.getLength() ; i++) 
            {
                Node nd = nl.item(i);
                nd.getFirstChild().setNodeValue(Double.toString(new_value));
            }            
        } catch (XPathExpressionException ex)
        {
            Logger.getLogger(AdaptMetronamicaProjectFile.class.getName()).log(Level.SEVERE, null, ex);
        }   
    }
    
    static void set_all_values2(XPathFactory xPathFactory, Document doc, String xpath_query, int new_value)
    {
        try
        {
            // TODO code application logic here
            
            XPath xpath = xPathFactory.newXPath();
            XPathExpression expr = xpath.compile(xpath_query);
            NodeList nl = (NodeList) expr.evaluate(doc, XPathConstants.NODESET);
            for(int i=0; i<nl.getLength() ; i++) 
            {
                Node nd = nl.item(i);
                nd.getFirstChild().setNodeValue(Integer.toString(new_value));
            }            
        } catch (XPathExpressionException ex)
        {
            Logger.getLogger(AdaptMetronamicaProjectFile.class.getName()).log(Level.SEVERE, null, ex);
        }   
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        XPathFactory xPathFactory = null;
        xPathFactory = XPathFactory.newInstance();
       
        
        String filename = args[0];
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        
        DocumentBuilder builder = null;
        try
        {
            builder = factory.newDocumentBuilder();
        } catch (ParserConfigurationException ex)
        {
            Logger.getLogger(AdaptMetronamicaProjectFile.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        Document doc = null;
        try
        {
            doc = builder.parse(new File(filename));
         } catch (SAXException | IOException ex)
        {
            Logger.getLogger(AdaptMetronamicaProjectFile.class.getName()).log(Level.SEVERE, null, ex);
        }
                    
        
        double[] dvs = new double[370];
        
//        try (Scanner in = new Scanner(args[2]))
//        {
//            int i = 0;
//            while (in.hasNextDouble())
//            {
//                dvs[i] = in.nextDouble();
//            }
////        //Read in decision variables
////        BufferedReader in = null;
////        in = new BufferedReader(new FileReader(args[2]));
////        
////        String l;
////        int i = 0;
////            while((l = in.readLine()) != null)
////            {
////                dvs[i] = l;
////                i++;
////            }
//        }

        for (int i = 0; i < 369; i++)
        {
            dvs[i] = Double.parseDouble(args[i+2]);
        }
//        
        
        //// Parameters - Inertia Neighbourhood Rules
            // Greenhouses (Function Class 1)
        // From GREenhouses to GREenhouses
        double gregre1 = dvs[0];
        double gregre2 = dvs[1];
        double gregre3 = dvs[2];
            // Housing Low Density (Function Class 2)
        // From Housing Low Density to Housing Low Density
        double hldhld1 = dvs[3];
        double hldhld2 = dvs[4];
        double hldhld3 = dvs[5];
             // Housing High Density (Function Class 3)
         // From Housing High Density to Housing High Density
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
             // Socio-cultural uses (Function class 6)
         // From Socio-Cultural Uses to Socio-Cultural Uses
        double scuscu1 = dvs[15];
        double scuscu2 = dvs[16];
        double scuscu3 = dvs[17];
             // Forest (Function class 7)
         // From FORest to FORest
        double forfor1 = dvs[18];
        double forfor2 = dvs[19];
        double forfor3 = dvs[20];
             // Extensive Grasslands (Function class 8)
         // From EXtensive Grasslands to EXtensive Grasslands
        double exgexg1 = dvs[21];
        double exgexg2 = dvs[22];
        double exgexg3 = dvs[23];
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
         // From PAStures to GREenhouses
        double pasgre1 = dvs[32];
        double pasgre2 = dvs[33];
         // From ARable Land to GREenhouses 
        double arlgre1 = dvs[34];
        double arlgre2 = dvs[35];
         // From Housing Low Density to GREenhouses
        double hldgre1 = dvs[36];
        double hldgre2 = dvs[37];
         // From Housing High Density to GREenhouses
        double hhdgre1 = dvs[38];
        double hhdgre2 = dvs[39];
         // From INDustry to GREenhouses
        double indgre1 = dvs[40];
        double indgre2 = dvs[41];
         // From SERvices to GREenhouses
        double sergre1 = dvs[42];
        double sergre2 = dvs[43];
         // From Socio-Cultural Uses to GREenhouses
        double scugre1 = dvs[44];
        double scugre2 = dvs[45];
         // From FORest to GREeehouses
        double forgre1 = dvs[46];
        double forgre2 = dvs[47];
         // From EXtensive Grasslands to GREenhouses
        double exggre1 = dvs[48];
        double exggre2 = dvs[49];
         // From NATure to GREenhouses
        double natgre1 = dvs[50];
        double natgre2 = dvs[51];
         // From RECreation areas to GREenhouses
        double recgre1 = dvs[52];
        double recgre2 = dvs[53];
         // From AIRport to GREenhouses
        double airgre1 = dvs[54];
        double airgre2 = dvs[55];
         // From FREsh water to GREenhouses
        double fregre1 = dvs[56];
        double fregre2 = dvs[57];
         // From MARine water to GREenhouses
        double margre1 = dvs[58];
        double margre2 = dvs[59];
             // Housing Low Density (Function Class 2)
         // From Other AGriculture to Housing Low Density
        double oaghld1 = dvs[60];
        double oaghld2 = dvs[61];
         // From PAStures to Housing Low Density
        double pashld1 = dvs[62];
        double pashld2 = dvs[63];
         // From ARable Land to Housing Low Density 
        double arlhld1 = dvs[64];
        double arlhld2 = dvs[65];
         // From GREenhouses to Housing Low Density
        double grehld1 = dvs[66];
        double grehld2 = dvs[67];
         // From Housing High Density to Housing Low Density
        double hhdhld1 = dvs[68];
        double hhdhld2 = dvs[69];
         // From INDustry to Housing Low Density
        double indhld1 = dvs[70];
        double indhld2 = dvs[71];
         // From SERvices to Housing Low Density
        double serhld1 = dvs[72];
        double serhld2 = dvs[73];
         // From Socio-Cultural Uses to Housing Low Density
        double scuhld1 = dvs[74];
        double scuhld2 = dvs[75];
         // From FORest to Housing Low Density
        double forhld1 = dvs[76];
        double forhld2 = dvs[77];
         // From EXtensive Grasslands to Housing Low Density
        double exghld1 = dvs[78];
        double exghld2 = dvs[79];
         // From NATure to Housing Low Density
        double nathld1 = dvs[80];
        double nathld2 = dvs[81];
         // From RECreation areas to Housing Low Density
        double rechld1 = dvs[82];
        double rechld2 = dvs[83];
         // From AIRport to Housing Low Density
        double airhld1 = dvs[84];
        double airhld2 = dvs[85];
         // From FREsh water to Housing Low Density
        double frehld1 = dvs[86];
        double frehld2 = dvs[87];
         // From MARine water to Housing Low Density
        double marhld1 = dvs[88];
        double marhld2 = dvs[89];
             // Housing High Density (Function Class 3)
         // From Other AGriculture to Housing High Density
        double oaghhd1 = dvs[90];
        double oaghhd2 = dvs[91];
         // From PAStures to Housing High Density
        double pashhd1 = dvs[92];
        double pashhd2 = dvs[93];
         // From ARable Land to Housing High Density 
        double arlhhd1 = dvs[94];
        double arlhhd2 = dvs[95];
         // From GREenhouses to Housing High Density
        double grehhd1 = dvs[96];
        double grehhd2 = dvs[97];
         // From Housing Low Density to Housing High Density
        double hldhhd1 = dvs[98];
        double hldhhd2 = dvs[99];    
         // From INDustry to Housing High Density
        double indhhd1 = dvs[100];
        double indhhd2 = dvs[101];
         // From SERvices to Housing High Density
        double serhhd1 = dvs[102];
        double serhhd2 = dvs[103];
         // From Socio-Cultural Uses to Housing High Density
        double scuhhd1 = dvs[104];
        double scuhhd2 = dvs[105];
         // From FORest to Housing High Density
        double forhhd1 = dvs[106];
        double forhhd2 = dvs[107];
         // From EXtensive Grasslands to Housing High Density
        double exghhd1 = dvs[108];
        double exghhd2 = dvs[109];
         // From NATure to Housing High Density
        double nathhd1 = dvs[110];
        double nathhd2 = dvs[111];
         // From RECreation areas to Housing High Density
        double rechhd1 = dvs[112];
        double rechhd2 = dvs[113];
         // From AIRport to Housing High Density
        double airhhd1 = dvs[114];
        double airhhd2 = dvs[115];
         // From FREsh water to Housing High Density
        double frehhd1 = dvs[116];
        double frehhd2 = dvs[117];
         // From MARine water to Housing High Density
        double marhhd1 = dvs[118];
        double marhhd2 = dvs[119];
             // Industry (Function Class 4)
         // From Other AGriculture to INDustry
        double oagind1 = dvs[120];
        double oagind2 = dvs[121];
         // From PAStures to INDustry
        double pasind1 = dvs[122];
        double pasind2 = dvs[123];
         // From ARable Land to INDustry 
        double arlind1 = dvs[124];
        double arlind2 = dvs[125];
         // From GREenhouses to INDustry
        double greind1 = dvs[126];
        double greind2 = dvs[127];
         // From Housing Low Density to INDustry
        double hldind1 = dvs[128];
        double hldind2 = dvs[129];
         // From Housing High Density to INDustry
        double hhdind1 = dvs[130];
        double hhdind2 = dvs[131];
         // From SERvices to INDustry
        double serind1 = dvs[132];
        double serind2 = dvs[133];
         // From Socio-Cultural Uses to INDustry
        double scuind1 = dvs[134];
        double scuind2 = dvs[135];
         // From FORest to INDustry
        double forind1 = dvs[136];
        double forind2 = dvs[137];
         // From EXtensive Grasslands to INDustry
        double exgind1 = dvs[138];
        double exgind2 = dvs[139];
         // From NATure to INDustry
        double natind1 = dvs[140];
        double natind2 = dvs[141];
         // From RECreation areas to INDustry
        double recind1 = dvs[142];
        double recind2 = dvs[143];
         // From AIRport to INDustry
        double airind1 = dvs[144];
        double airind2 = dvs[145];
         // From FREsh water to INDustry
        double freind1 = dvs[146];
        double freind2 = dvs[147];
         // From MARine water to INDustry
        double marind1 = dvs[148];
        double marind2 = dvs[149];
             // Services (Function Class 5)
         // From Other AGriculture to SERvices
        double oagser1 = dvs[150];
        double oagser2 = dvs[151];
         // From PAStures to SERvices
        double passer1 = dvs[152];
        double passer2 = dvs[153];
         // From ARable Land to SERvices 
        double arlser1 = dvs[154];
        double arlser2 = dvs[155];
         // From GREenhouses to SERvices
        double greser1 = dvs[156];
        double greser2 = dvs[157];
         // From Housing Low Density to SERvices
        double hldser1 = dvs[158];
        double hldser2 = dvs[159];
         // From Housing High Density to SERvices
        double hhdser1 = dvs[160];
        double hhdser2 = dvs[161];
         // From INDustry to SERvices
        double indser1 = dvs[162];
        double indser2 = dvs[163];
         // From Socio-Cultural uses to SERvices
        double scuser1 = dvs[164];
        double scuser2 = dvs[165];
         // From FORest to SERvices
        double forser1 = dvs[166];
        double forser2 = dvs[167];
         // From EXtensive Grasslands to SERvices
        double exgser1 = dvs[168];
        double exgser2 = dvs[169];
         // From NATure to SERvices
        double natser1 = dvs[170];
        double natser2 = dvs[171];
         // From RECreation areas to SERvices
        double recser1 = dvs[172];
        double recser2 = dvs[173];
         // From AIRport to SERvices
        double airser1 = dvs[174];
        double airser2 = dvs[175];
         // From FREsh water to SERvices
        double freser1 = dvs[176];
        double freser2 = dvs[177];
         // From MARine water to SERvices
        double marser1 = dvs[178];
        double marser2 = dvs[179];
             // Socio-cultural uses (Function class 6)
         // From Other AGriculture to Socio-Cultural Uses
        double oagscu1 = dvs[180];
        double oagscu2 = dvs[181];
         // From PAStures to Soio-Cultural Uses
        double passcu1 = dvs[182];
        double passcu2 = dvs[183];
         // From ARable Land to Socio-Cultural Uses 
        double arlscu1 = dvs[184];
        double arlscu2 = dvs[185];
         // From GREenhouses toSocio-Cultural Uses
        double grescu1 = dvs[186];
        double grescu2 = dvs[187];
         // From Housing Low Density to Socio-Cultural Uses
        double hldscu1 = dvs[188];
        double hldscu2 = dvs[189];
         // From Housing High Density to Socio-Cultural Uses
        double hhdscu1 = dvs[190];
        double hhdscu2 = dvs[191];
         // From INDustry to Socio-Cultural Uses
        double indscu1 = dvs[192];
        double indscu2 = dvs[193];
         // From SERvices to Socio-Cultural Uses
        double serscu1 = dvs[194];
        double serscu2 = dvs[195];
         // From FORest to Socio-cultural Uses
        double forscu1 = dvs[196];
        double forscu2 = dvs[197];
         // From EXtensive Grasslands to Socio-Cultural Uses
        double exgscu1 = dvs[198];
        double exgscu2 = dvs[199];
         // From NATure to Socio-Cultural Uses
        double natscu1 = dvs[200];
        double natscu2 = dvs[201];
         // From RECreation areas to Socio-Cultural Uses
        double recscu1 = dvs[202];
        double recscu2 = dvs[203];
         // From AIRport to Socio-Cultural Uses
        double airscu1 = dvs[204];
        double airscu2 = dvs[205];
         // From FREsh water toSocio-Cultural Uses
        double frescu1 = dvs[206];
        double frescu2 = dvs[207];
         // From MARine water to Socio-Cultural Uses
        double marscu1 = dvs[208];
        double marscu2 = dvs[209];
             // Forest (Function class 7)
         // From Other AGriculture to FORest
        double oagfor1 = dvs[210];
        double oagfor2 = dvs[211];
         // From PAStures to FORest
        double pasfor1 = dvs[212];
        double pasfor2 = dvs[213];
         // From ARable Land to FORest
        double arlfor1 = dvs[214];
        double arlfor2 = dvs[215];
         // From GREenhouses to FORest
        double grefor1 = dvs[216];
        double grefor2 = dvs[217];
         // From Housing Low Density to FORest
        double hldfor1 = dvs[218];
        double hldfor2 = dvs[219];
         // From Housing High Density to FORest
        double hhdfor1 = dvs[220];
        double hhdfor2 = dvs[221];
         // From INDustry to FORest
        double indfor1 = dvs[222];
        double indfor2 = dvs[223];
         // From SERvices to FORest
        double serfor1 = dvs[224];
        double serfor2 = dvs[225];
         // From Socio-Cultural Uses to FORest
        double scufor1 = dvs[226];
        double scufor2 = dvs[227];
         // From EXtensive Grasslands to FORest
        double exgfor1 = dvs[228];
        double exgfor2 = dvs[229];
         // From NATure to FORest
        double natfor1 = dvs[230];
        double natfor2 = dvs[231];
         // From RECreation areas to FORest
        double recfor1 = dvs[232];
        double recfor2 = dvs[233];
         // From AIRport to FORest
        double airfor1 = dvs[234];
        double airfor2 = dvs[235];
         // From FREsh water to FORest
        double frefor1 = dvs[236];
        double frefor2 = dvs[237];
         // From MARine water to FORest
        double marfor1 = dvs[238];
        double marfor2 = dvs[239];
             // Extensive Grasslands (Function class 8)
         // From Other AGriculture to EXtensive Grasslands
        double oagexg1 = dvs[240];
        double oagexg2 = dvs[241];
         // From PAStures to EXtensive Grasslands
        double pasexg1 = dvs[242];
        double pasexg2 = dvs[243];
         // From ARable Land to EXtensive Grasslands 
        double arlexg1 = dvs[244];
        double arlexg2 = dvs[245];
         // From GREenhouses toEXtensive Grasslands
        double greexg1 = dvs[246];
        double greexg2 = dvs[247];
         // From Housing Low Density to EXtensive Grasslands
        double hldexg1 = dvs[248];
        double hldexg2 = dvs[249];
         // From Housing High Density to EXtensive Grasslands
        double hhdexg1 = dvs[250];
        double hhdexg2 = dvs[251];
         // From INDustry to EXtensive Grasslands
        double indexg1 = dvs[252];
        double indexg2 = dvs[253];
         // From SERvices to EXtensive Grasslands
        double serexg1 = dvs[254];
        double serexg2 = dvs[255];
         // From Socio-Cultural Uses to EXtensive Grasslands
        double scuexg1 = dvs[256];
        double scuexg2 = dvs[257];
         // From FORest to EXtensive Grasslands
        double forexg1 = dvs[258];
        double forexg2 = dvs[259];
         // From NATure to EXtensive Grasslands
        double natexg1 = dvs[260];
        double natexg2 = dvs[261];
         // From RECreation areas to EXtensive Grasslands
        double recexg1 = dvs[262];
        double recexg2 = dvs[263];
         // From AIRport to EXtensive Grasslands
        double airexg1 = dvs[264];
        double airexg2 = dvs[265];
         // From FREsh water to EXtensive Grasslands
        double freexg1 = dvs[266];
        double freexg2 = dvs[267];
         // From MARine water to EXtensive Grasslands
        double marexg1 = dvs[268];
        double marexg2 = dvs[269];
             // Nature (Function class 9)
         // From Other AGriculture to NATure
        double oagnat1 = dvs[270];
        double oagnat2 = dvs[271];
         // From PAStures to NATure
        double pasnat1 = dvs[272];
        double pasnat2 = dvs[273];
         // From ARable Land to NATure 
        double arlnat1 = dvs[274];
        double arlnat2 = dvs[275];
         // From GREenhouses to NATure
        double grenat1 = dvs[276];
        double grenat2 = dvs[277];
         // From Housing Low Density to NATure
        double hldnat1 = dvs[278];
        double hldnat2 = dvs[279];
         // From Housing High Density to NATure
        double hhdnat1 = dvs[280];
        double hhdnat2 = dvs[281];
         // From INDustry to NATure
        double indnat1 = dvs[282];
        double indnat2 = dvs[283];
         // From SERvices to NATure
        double sernat1 = dvs[284];
        double sernat2 = dvs[285];
         // From Socio-Cultural Uses to NATure
        double scunat1 = dvs[286];
        double scunat2 = dvs[287];
         // From FORest to NATure
        double fornat1 = dvs[288];
        double fornat2 = dvs[289];
         // From EXtensive Grasslands to NATure
        double exgnat1 = dvs[290];
        double exgnat2 = dvs[291];
         // From RECreation ares to NATure
        double recnat1 = dvs[292];
        double recnat2 = dvs[293];
         // From AIRport to NATure
        double airnat1 = dvs[294];
        double airnat2 = dvs[295];
         // From FREsh water to NATure
        double frenat1 = dvs[296];
        double frenat2 = dvs[297];
         // From MARine water to NATure
        double marnat1 = dvs[298];
        double marnat2 = dvs[299];
             // Recreation Areas (Function class 10)
         // From Other AGriculture to RECreation areas
        double oagrec1 = dvs[300];
        double oagrec2 = dvs[301];
         // From PAStures to RECreation areas
        double pasrec1 = dvs[302];
        double pasrec2 = dvs[303];
         // From ARable Land to RECreation areas 
        double arlrec1 = dvs[304];
        double arlrec2 = dvs[305];
         // From GREenhouses to RECreation areas
        double grerec1 = dvs[306];
        double grerec2 = dvs[307];
         // From Housing Low Density to RECreation areas
        double hldrec1 = dvs[308];
        double hldrec2 = dvs[309];
         // From Housing High Density to RECreation areas
        double hhdrec1 = dvs[310];
        double hhdrec2 = dvs[311];
         // From INDustry to RECreation areas
        double indrec1 = dvs[312];
        double indrec2 = dvs[313];
         // From SERvices to RECreation areas
        double serrec1 = dvs[314];
        double serrec2 = dvs[315];
         // From Socio-Cultural Uses to RECreation areas
        double scurec1 = dvs[316];
        double scurec2 = dvs[317];
         // From FORest to RECreation areas
        double forrec1 = dvs[318];
        double forrec2 = dvs[319];
         // From EXtensive Grasslands to RECreation areas
        double exgrec1 = dvs[320];
        double exgrec2 = dvs[321];
         // From NATure to RECreation areas
        double natrec1 = dvs[322];
        double natrec2 = dvs[323];
         // From AIRport to RECreation areas
        double airrec1 = dvs[324];
        double airrec2 = dvs[325];
         // From FREsh water to RECreation areas
        double frerec1 = dvs[326];
        double frerec2 = dvs[327];
         // From MARine water to RECreation areas
        double marrec1 = dvs[328];
        double marrec2 = dvs[329];

         //// Parameters - Accessibility distance decay
         // Greenhouses
        double gremdd = dvs[330];
        double greodd = dvs[331];
         // Housing low density
        double hldmdd = dvs[332];
        double hldodd = dvs[333];
         // Housing high density
        double hhdmdd = dvs[334];
        double hhdodd = dvs[335];
         // Industry
        double indmdd = dvs[336];
        double indodd = dvs[337];
         // Services
        double sermdd = dvs[338];
        double serodd = dvs[339];
         // Socio cultural Uses
        double scumdd = dvs[340];
        double scuodd = dvs[341];
         // Forest
        double formdd = dvs[342];
        double forodd = dvs[343];
         // Extensive grasslands
        double exgmdd = dvs[344];
        double exgodd = dvs[345];
         // Nature
        double natmdd = dvs[346];
        double natodd = dvs[347];
         // Recreation areas
        double recmdd = dvs[348];
        double recodd = dvs[349];
         //// Parameters - Accessibility Weights
         // Greenhouses
        double gremwe = dvs[350];
        double greowe = dvs[351];
         // Housing low density
        double hldmwe = dvs[352];
        double hldowe = dvs[353];
         // Housing high density
        double hhdmwe = dvs[354];
        double hhdowe = dvs[355];
         // Industry
        double indmwe = dvs[356];
        double indowe = dvs[357];
         // Services
        double sermwe = dvs[358];
        double serowe = dvs[359];
         // Socio cultural uses
        double scumwe = dvs[360];
        double scuowe = dvs[361];
         // Forest
        double formwe = dvs[362];
        double forowe = dvs[363];
         // Extensive grasslands
        double exgmwe = dvs[364];
        double exgowe = dvs[365];
         // Nature
        double natmwe = dvs[366];
        double natowe = dvs[367];
         // Recreation areas
        double recmwe = dvs[368];
        double recowe = dvs[369];
        
        int rseed = Integer.parseInt(args[372]);
          

        set_exp_rule_selfinfluence(xPathFactory, doc, 4, 1, gregre1, gregre2, gregre3);
        // Housing Low Density
        set_exp_rule_selfinfluence(xPathFactory, doc, 5, 2, hldhld1, hldhld2, hldhld3);
        // Housing High Density
        set_exp_rule_selfinfluence(xPathFactory, doc, 6, 3, hhdhhd1, hhdhhd2, hhdhhd3);
        // Industry
        set_exp_rule_selfinfluence(xPathFactory, doc, 7, 4, indind1, indind2, indind3);
        // Services
        set_exp_rule_selfinfluence(xPathFactory, doc, 8, 5, serser1, serser2, serser3);
        // Socio cultural uses
        set_exp_rule_selfinfluence(xPathFactory, doc, 9, 6, scuscu1, scuscu2, scuscu3);
        // Forest
        set_exp_rule_selfinfluence(xPathFactory, doc, 10, 7, forfor1, forfor2, forfor3);
        // Extensive grasslands
        set_exp_rule_selfinfluence(xPathFactory, doc, 11, 8, exgexg1, exgexg2, exgexg3);
        // Nature
        set_exp_rule_selfinfluence(xPathFactory, doc, 12, 9, natnat1, natnat2, natnat3);
        // Recreation areas
        set_exp_rule_selfinfluence(xPathFactory, doc, 13, 10, recrec1, recrec2, recrec3);

        // Amend Iteraction Neighbourhood Rules
        // Greenhouses
        set_exp_rule_interaction(xPathFactory, doc, 1, 1, oaggre1, oaggre2);
        set_exp_rule_interaction(xPathFactory, doc, 2, 1, pasgre1, pasgre2);
        set_exp_rule_interaction(xPathFactory, doc, 3, 1, arlgre1, arlgre2);
        set_exp_rule_interaction(xPathFactory, doc, 5, 1, hldgre1, hldgre2);
        set_exp_rule_interaction(xPathFactory, doc, 6, 1, hhdgre1, hhdgre2);
        set_exp_rule_interaction(xPathFactory, doc, 7, 1, indgre1, indgre2);
        set_exp_rule_interaction(xPathFactory, doc, 8, 1, sergre1, sergre2);
        set_exp_rule_interaction(xPathFactory, doc, 9, 1, scugre1, scugre2);
        set_exp_rule_interaction(xPathFactory, doc, 10, 1, forgre1, forgre2);
        set_exp_rule_interaction(xPathFactory, doc, 11, 1, exggre1, exggre2);
        set_exp_rule_interaction(xPathFactory, doc, 12, 1, natgre1, natgre2);
        set_exp_rule_interaction(xPathFactory, doc, 13, 1, recgre1, recgre2);
        set_exp_rule_interaction(xPathFactory, doc, 14, 1, airgre1, airgre2);
        set_exp_rule_interaction(xPathFactory, doc, 15, 1, fregre1, fregre2);
        set_exp_rule_interaction(xPathFactory, doc, 16, 1, margre1, margre2);
        // Housing Low Density
        set_exp_rule_interaction(xPathFactory, doc, 1, 2, oaghld1, oaghld2); 
        set_exp_rule_interaction(xPathFactory, doc, 2, 2, pashld1, pashld2);
        set_exp_rule_interaction(xPathFactory, doc, 3, 2, arlhld1, arlhld2);
        set_exp_rule_interaction(xPathFactory, doc, 4, 2, grehld1, grehld2);
        set_exp_rule_interaction(xPathFactory, doc, 6, 2, hhdhld1, hhdhld2);
        set_exp_rule_interaction(xPathFactory, doc, 7, 2, indhld1, indhld2);
        set_exp_rule_interaction(xPathFactory, doc, 8, 2, serhld1, serhld2);
        set_exp_rule_interaction(xPathFactory, doc, 9, 2, scuhld1, scuhld2);
        set_exp_rule_interaction(xPathFactory, doc, 10, 2, forhld1, forhld2);
        set_exp_rule_interaction(xPathFactory, doc, 11, 2, exghld1, exghld2);
        set_exp_rule_interaction(xPathFactory, doc, 12, 2, nathld1, nathld2);
        set_exp_rule_interaction(xPathFactory, doc, 13, 2, rechld1, rechld2);
        set_exp_rule_interaction(xPathFactory, doc, 14, 2, airhld1, airhld2);
        set_exp_rule_interaction(xPathFactory, doc, 15, 2, frehld1, frehld2);
        set_exp_rule_interaction(xPathFactory, doc, 16, 2, marhld1, marhld2);
        // Housing High Density
        set_exp_rule_interaction(xPathFactory, doc, 1, 3, oaghhd1, oaghhd2);
        set_exp_rule_interaction(xPathFactory, doc, 2, 3, pashhd1, pashhd2);
        set_exp_rule_interaction(xPathFactory, doc, 3, 3, arlhhd1, arlhhd2);
        set_exp_rule_interaction(xPathFactory, doc, 4, 3, grehhd1, grehhd2);
        set_exp_rule_interaction(xPathFactory, doc, 5, 3, hldhhd1, hldhhd2);
        set_exp_rule_interaction(xPathFactory, doc, 7, 3, indhhd1, indhhd2);
        set_exp_rule_interaction(xPathFactory, doc, 8, 3, serhhd1, serhhd2);
        set_exp_rule_interaction(xPathFactory, doc, 9, 3, scuhhd1, scuhhd2);
        set_exp_rule_interaction(xPathFactory, doc, 10, 3, forhhd1, forhhd2);
        set_exp_rule_interaction(xPathFactory, doc, 11, 3, exghhd1, exghhd2);
        set_exp_rule_interaction(xPathFactory, doc, 12, 3, nathhd1, nathhd2);
        set_exp_rule_interaction(xPathFactory, doc, 13, 3, rechhd1, rechhd2);
        set_exp_rule_interaction(xPathFactory, doc, 14, 3, airhhd1, airhhd2);
        set_exp_rule_interaction(xPathFactory, doc, 15, 3, frehhd1, frehhd2);
        set_exp_rule_interaction(xPathFactory, doc, 16, 3, marhhd1, marhhd2);
        // Industry
        set_exp_rule_interaction(xPathFactory, doc, 1, 4, oagind1, oagind2);
        set_exp_rule_interaction(xPathFactory, doc, 2, 4, pasind1, pasind2);
        set_exp_rule_interaction(xPathFactory, doc, 3, 4, arlind1, arlind2);
        set_exp_rule_interaction(xPathFactory, doc, 4, 4, greind1, greind2);
        set_exp_rule_interaction(xPathFactory, doc, 5, 4, hldind1, hldind2);
        set_exp_rule_interaction(xPathFactory, doc, 6, 4, hhdind1, hhdind2);
        set_exp_rule_interaction(xPathFactory, doc, 8, 4, serind1, serind2);
        set_exp_rule_interaction(xPathFactory, doc, 9, 4, scuind1, scuind2);
        set_exp_rule_interaction(xPathFactory, doc, 10, 4, forind1, forind2);
        set_exp_rule_interaction(xPathFactory, doc, 11, 4, exgind1, exgind2);
        set_exp_rule_interaction(xPathFactory, doc, 12, 4, natind1, natind2);
        set_exp_rule_interaction(xPathFactory, doc, 13, 4, recind1, recind2);
        set_exp_rule_interaction(xPathFactory, doc, 14, 4, airind1, airind2);
        set_exp_rule_interaction(xPathFactory, doc, 15, 4, freind1, freind2);
        set_exp_rule_interaction(xPathFactory, doc, 16, 4, marind1, marind2);
        // Services
        set_exp_rule_interaction(xPathFactory, doc, 1, 5, oagser1, oagser2);
        set_exp_rule_interaction(xPathFactory, doc, 2, 5, passer1, passer2);
        set_exp_rule_interaction(xPathFactory, doc, 3, 5, arlser1, arlser2);
        set_exp_rule_interaction(xPathFactory, doc, 4, 5, greser1, greser2);
        set_exp_rule_interaction(xPathFactory, doc, 5, 5, hldser1, hldser2);
        set_exp_rule_interaction(xPathFactory, doc, 6, 5, hhdser1, hhdser2);
        set_exp_rule_interaction(xPathFactory, doc, 7, 5, indser1, indser2);
        set_exp_rule_interaction(xPathFactory, doc, 9, 5, scuser1, scuser2);
        set_exp_rule_interaction(xPathFactory, doc, 10, 5, forser1, forser2);
        set_exp_rule_interaction(xPathFactory, doc, 11, 5, exgser1, exgser2);
        set_exp_rule_interaction(xPathFactory, doc, 12, 5, natser1, natser2);
        set_exp_rule_interaction(xPathFactory, doc, 13, 5, recser1, recser2);
        set_exp_rule_interaction(xPathFactory, doc, 14, 5, airser1, airser2);
        set_exp_rule_interaction(xPathFactory, doc, 15, 5, freser1, freser2);
        set_exp_rule_interaction(xPathFactory, doc, 16, 5, marser1, marser2);
        // Socio cultural uses
        set_exp_rule_interaction(xPathFactory, doc, 1, 6, oagscu1, oagscu2);
        set_exp_rule_interaction(xPathFactory, doc, 2, 6, passcu1, passcu2);
        set_exp_rule_interaction(xPathFactory, doc, 3, 6, arlscu1, arlscu2);
        set_exp_rule_interaction(xPathFactory, doc, 4, 6, grescu1, grescu2);
        set_exp_rule_interaction(xPathFactory, doc, 5, 6, hldscu1, hldscu2);
        set_exp_rule_interaction(xPathFactory, doc, 6, 6, hhdscu1, hhdscu2);
        set_exp_rule_interaction(xPathFactory, doc, 7, 6, indscu1, indscu2);
        set_exp_rule_interaction(xPathFactory, doc, 8, 6, serscu1, serscu2);
        set_exp_rule_interaction(xPathFactory, doc, 10, 6, forscu1, forscu2);
        set_exp_rule_interaction(xPathFactory, doc, 11, 6, exgscu1, exgscu2);
        set_exp_rule_interaction(xPathFactory, doc, 12, 6, natscu1, natscu2);
        set_exp_rule_interaction(xPathFactory, doc, 13, 6, recscu1, recscu2);
        set_exp_rule_interaction(xPathFactory, doc, 14, 6, airscu1, airscu2);
        set_exp_rule_interaction(xPathFactory, doc, 15, 6, frescu1, frescu2);
        set_exp_rule_interaction(xPathFactory, doc, 16, 6, marscu1, marscu2);
        // Forest
        set_exp_rule_interaction(xPathFactory, doc, 1, 7, oagfor1, oagfor2);
        set_exp_rule_interaction(xPathFactory, doc, 2, 7, pasfor1, pasfor2);
        set_exp_rule_interaction(xPathFactory, doc, 3, 7, arlfor1, arlfor2);
        set_exp_rule_interaction(xPathFactory, doc, 4, 7, grefor1, grefor2);
        set_exp_rule_interaction(xPathFactory, doc, 5, 7, hldfor1, hldfor2);
        set_exp_rule_interaction(xPathFactory, doc, 6, 7, hhdfor1, hhdfor2);
        set_exp_rule_interaction(xPathFactory, doc, 7, 7, indfor1, indfor2);
        set_exp_rule_interaction(xPathFactory, doc, 8, 7, serfor1, serfor2);
        set_exp_rule_interaction(xPathFactory, doc, 9, 7, scufor1, scufor2);
        set_exp_rule_interaction(xPathFactory, doc, 11, 7, exgfor1, exgfor2);
        set_exp_rule_interaction(xPathFactory, doc, 12, 7, natfor1, natfor2);
        set_exp_rule_interaction(xPathFactory, doc, 13, 7, recfor1, recfor2);
        set_exp_rule_interaction(xPathFactory, doc, 14, 7, airfor1, airfor2);
        set_exp_rule_interaction(xPathFactory, doc, 15, 7, frefor1, frefor2);
        set_exp_rule_interaction(xPathFactory, doc, 16, 7, marfor1, marfor2);
        // Extensive grasslands
        set_exp_rule_interaction(xPathFactory, doc, 1, 8, oagexg1, oagexg2);
        set_exp_rule_interaction(xPathFactory, doc, 2, 8, pasexg1, pasexg2);
        set_exp_rule_interaction(xPathFactory, doc, 3, 8, arlexg1, arlexg2);
        set_exp_rule_interaction(xPathFactory, doc, 4, 8, greexg1, greexg2);
        set_exp_rule_interaction(xPathFactory, doc, 5, 8, hldexg1, hldexg2);
        set_exp_rule_interaction(xPathFactory, doc, 6, 8, hhdexg1, hhdexg2);
        set_exp_rule_interaction(xPathFactory, doc, 7, 8, indexg1, indexg2);
        set_exp_rule_interaction(xPathFactory, doc, 8, 8, serexg1, serexg2);
        set_exp_rule_interaction(xPathFactory, doc, 9, 8, scuexg1, scuexg2);
        set_exp_rule_interaction(xPathFactory, doc, 10, 8, forexg1, forexg2);
        set_exp_rule_interaction(xPathFactory, doc, 12, 8, natexg1, natexg2);
        set_exp_rule_interaction(xPathFactory, doc, 13, 8, recexg1, recexg2);
        set_exp_rule_interaction(xPathFactory, doc, 14, 8, airexg1, airexg2);
        set_exp_rule_interaction(xPathFactory, doc, 15, 8, freexg1, freexg2);
        set_exp_rule_interaction(xPathFactory, doc, 16, 8, marexg1, marexg2);
        // Nature
        set_exp_rule_interaction(xPathFactory, doc, 1, 9, oagnat1, oagnat2);
        set_exp_rule_interaction(xPathFactory, doc, 2, 9, pasnat1, pasnat2);
        set_exp_rule_interaction(xPathFactory, doc, 3, 9, arlnat1, arlnat2);
        set_exp_rule_interaction(xPathFactory, doc, 4, 9, grenat1, grenat2);
        set_exp_rule_interaction(xPathFactory, doc, 5, 9, hldnat1, hldnat2);
        set_exp_rule_interaction(xPathFactory, doc, 6, 9, hhdnat1, hhdnat2);
        set_exp_rule_interaction(xPathFactory, doc, 7, 9, indnat1, indnat2);
        set_exp_rule_interaction(xPathFactory, doc, 8, 9, sernat1, sernat2);
        set_exp_rule_interaction(xPathFactory, doc, 9, 9, scunat1, scunat2);
        set_exp_rule_interaction(xPathFactory, doc, 10, 9, fornat1, fornat2);
        set_exp_rule_interaction(xPathFactory, doc, 11, 9, exgnat1, exgnat2);
        set_exp_rule_interaction(xPathFactory, doc, 13, 9, recnat1, recnat2);
        set_exp_rule_interaction(xPathFactory, doc, 14, 9, airnat1, airnat2);
        set_exp_rule_interaction(xPathFactory, doc, 15, 9, frenat1, frenat2);
        set_exp_rule_interaction(xPathFactory, doc, 16, 9, marnat1, marnat2);
        // Recreation areas
        set_exp_rule_interaction(xPathFactory, doc, 1, 10, oagrec1, oagrec2);
        set_exp_rule_interaction(xPathFactory, doc, 2, 10, pasrec1, pasrec2);
        set_exp_rule_interaction(xPathFactory, doc, 3, 10, arlrec1, arlrec2);
        set_exp_rule_interaction(xPathFactory, doc, 4, 10, grerec1, grerec2);
        set_exp_rule_interaction(xPathFactory, doc, 5, 10, hldrec1, hldrec2);
        set_exp_rule_interaction(xPathFactory, doc, 6, 10, hhdrec1, hhdrec2);
        set_exp_rule_interaction(xPathFactory, doc, 7, 10, indrec1, indrec2);
        set_exp_rule_interaction(xPathFactory, doc, 8, 10, serrec1, serrec2);
        set_exp_rule_interaction(xPathFactory, doc, 9, 10, scurec1, scurec2);
        set_exp_rule_interaction(xPathFactory, doc, 10, 10, forrec1, forrec2);
        set_exp_rule_interaction(xPathFactory, doc, 11, 10, exgrec1, exgrec2);
        set_exp_rule_interaction(xPathFactory, doc, 12, 10, natrec1, natrec2);
        set_exp_rule_interaction(xPathFactory, doc, 14, 10, airrec1, airrec2);
        set_exp_rule_interaction(xPathFactory, doc, 15, 10, frerec1, frerec2);
        set_exp_rule_interaction(xPathFactory, doc, 16, 10, marrec1, marrec2);

//        % Amend Accessibility
//    % Motorway distance decay
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[1]", gremdd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[2]", hldmdd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[3]", hhdmdd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[4]", indmdd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[5]", sermdd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[6]", scumdd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[7]", formdd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[8]", exgmdd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[9]", natmdd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[10]", recmdd);
//        % Other roads distance decay
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[1]", greodd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[2]", hldodd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[3]", hhdodd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[4]", indodd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[5]", serodd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[6]", scuodd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[7]", forodd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[8]", exgodd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[9]", natodd);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/DistanceDecay/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[10]", recodd);
//        % Motorway weights
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[1]", gremwe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[2]", hldmwe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[3]", hhdmwe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[4]", indmwe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[5]", sermwe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[6]", scumwe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[7]", formwe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[8]", exgmwe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[9]", natmwe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[1]/vector/elem[10]", recmwe);
//        % Other roads weights
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[1]", greowe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[2]", hldowe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[3]", hhdowe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[4]", indowe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[5]", serowe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[6]", scuowe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[7]", forowe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[8]", exgowe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[9]", natowe);
        set_all_values(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Accessibility\"]/AccessibilityWithZABlock/Weight/value[@time=\"1989-Jan-01 00:00:00\"]/vector/elem[2]/vector/elem[10]", recowe);

        set_all_values2(xPathFactory, doc, "/GeonamicaSimulation/model/modelBlocks/modelBlock[@library=\"\" and @name=\"MB_Land_use_model\"]/CompositeModelBlock/modelBlocks/modelBlock[@library=\"CAModel.dll\" and @name=\"MB_Total_potential\"]/TotalPotentialBlock/Seed", rseed);
         // Use a Transformer for output
    try
    {
    TransformerFactory tFactory = TransformerFactory.newInstance();
    Transformer transformer;
    transformer = tFactory.newTransformer();
        
    
    DOMSource source = new DOMSource(doc);
    StreamResult result = new StreamResult(new File(args[1]));
    transformer.transform(source, result);
    } catch (TransformerConfigurationException ex)
        {
            Logger.getLogger(AdaptMetronamicaProjectFile.class.getName()).log(Level.SEVERE, null, ex);
        } catch (TransformerException ex)
        {
            Logger.getLogger(AdaptMetronamicaProjectFile.class.getName()).log(Level.SEVERE, null, ex);
        }

    System.exit(0);
        
    }
    
}
