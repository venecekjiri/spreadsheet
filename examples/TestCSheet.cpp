#include <fstream>
#include <map>
#include <cassert>

#include "../src/CSheet.h"
#include "../src/CLinks.h"

using namespace std;

void TestSetAndDelete() {

    CSheet s0;

    assert("Cell not set as expected" && s0.SetCell("A9", "  15") && s0.GetValue("A9") == "15");
    assert("Cell not set as expected" && s0.SetCell("A8", "  =A9+15 ") && s0.GetValue("A8") == "30");
    assert("Cell not set as expected" && s0.SetCell("A7", " =A8-25") && s0.GetValue("A7") == "5");
    assert("Cell not set as expected" && s0.SetCell("A6", " =A7+5") && s0.GetValue("A6") == "10");
    assert("Cell not set as expected" && s0.SetCell("A5", " =A6-5") && s0.GetValue("A5") == "5");
    assert("Cell not set as expected" && s0.SetCell("A4", "=A5*2 ") && s0.GetValue("A4") == "10");
    assert("Cell not set as expected" && s0.SetCell("A3", "=A4/2") && s0.GetValue("A3") == "5");
    assert("Cell not set as expected" && s0.SetCell("A2", "=A3+5") && s0.GetValue("A2") == "10");
    assert("Cell not set as expected" && s0.SetCell("B2", "=A5-5") && s0.GetValue("B2") == "0");
    assert("Cell not set as expected" && s0.SetCell("B1", "=B2+5 ") && s0.GetValue("B1") == "5");
    assert("Cell not set as expected" && s0.SetCell("A1", "=B1+A2") && s0.GetValue("A1") == "15");

    assert("Cell not set as expected" && !s0.SetCell("A9", "=A4"));
    assert("Cell not set as expected" && !s0.SetCell("A6", "=A5"));
    assert("Cell not set as expected" && !s0.SetCell("A9", "=A1"));
    assert("Cell not set as expected" && !s0.SetCell("A9", "=B1"));

    assert("Cell not deleted as expected" && !s0.DeleteCell("A9"));
    assert("Cell not deleted as expected" && !s0.DeleteCell("A8"));
    assert("Cell not deleted as expected" && !s0.DeleteCell("A5"));
    assert("Cell not deleted as expected" && !s0.DeleteCell("B1"));
    assert("Cell not deleted as expected" && !s0.DeleteCell("A3"));
    assert("Cell not deleted as expected" && !s0.DeleteCell("A2"));

    assert("Cell not deleted as expected" && s0.DeleteCell("A1"));
    assert("Cell not deleted as expected" && s0.DeleteCell("A2"));
    assert("Cell not deleted as expected" && s0.DeleteCell("A3"));

    assert("Cell not set as expected" && s0.SetCell("B1", "=A4"));
    assert("Cell not set as expected" && s0.SetCell("A1", "=A5"));
    assert("Cell not set as expected" && s0.SetCell("A6", "=A9"));
}

void TestLoadingFromFile() {

    CSheet s0;

    /**
     * Valid file.
     * test0.txt is en example of valid sheet saved to file
     */
    assert("File not loaded" && s0.LoadFromFile("test0.txt"));

    assert("Invalid sheet contents" && s0.Find("D7") && s0.Print("D7") == "21.36");
    assert("Invalid sheet contents" && s0.Find("D5") && s0.Print("D5") == "=2*D7");
    assert("Invalid sheet contents" && s0.Find("C1") && s0.Print("C1") == "=D5/2");
    assert("Invalid sheet contents" && s0.Find("A2") && s0.Print("A2") == "=C1+5");
    assert("Invalid sheet contents" && s0.Find("C5") && s0.Print("C5") == "12");
    assert("Invalid sheet contents" && s0.Find("G3") && s0.Print("G3") == "125");
    assert("Invalid sheet contents" && s0.Find("G4") && s0.Print("G4") == "17");
    assert("Invalid sheet contents" && s0.Find("F1") && s0.Print("F1") == "=G3+G4");
    assert("Invalid sheet contents" && s0.Find("B4") && s0.Print("B4") == "=F1");
    assert("Invalid sheet contents" && s0.Find("D8") && s0.Print("D8") == "=5+8");
    assert("Invalid sheet contents" && s0.Find("B1") && s0.Print("B1") == "=D8+7");
    assert("Invalid sheet contents" && s0.Find("C2") && s0.Print("C2") == "=1/2");
    assert("Invalid sheet contents" && s0.Find("B2") && s0.Print("B2") == "=C2*2");
    assert("Invalid sheet contents" && s0.Find("A3") && s0.Print("A3") == "=B2");
    assert("Invalid sheet contents" && s0.Find("A1") && s0.Print("A1") == "=A2+A3+B1+B4");
    assert("Invalid sheet contents" && s0.Find("D9") && s0.Print("D9") == "=A1+5");
    assert("Invalid sheet contents" && s0.Find("C9") && s0.Print("C9") == "=D9-5");
    assert("Invalid sheet contents" && s0.Find("A4") && s0.Print("A4") == "Sum:");
    assert("Invalid sheet contents" && s0.Find("C10") && s0.Print("C10") == "Total:");
    assert("Invalid sheet contents" && s0.Find("D10") && s0.Print("D10") == "=D7");

    /*
     * Check if loading from file doesn't depend on the order of cells
     * test1.txt has cells stored in reversed order
     */
    assert("File not loaded" && s0.LoadFromFile("test1.txt"));

    assert("Invalid sheet contents" && s0.Find("D7") && s0.Print("D7") == "21.36");
    assert("Invalid sheet contents" && s0.Find("D5") && s0.Print("D5") == "=2*D7");
    assert("Invalid sheet contents" && s0.Find("C1") && s0.Print("C1") == "=D5/2");
    assert("Invalid sheet contents" && s0.Find("A2") && s0.Print("A2") == "=C1+5");
    assert("Invalid sheet contents" && s0.Find("C5") && s0.Print("C5") == "12");
    assert("Invalid sheet contents" && s0.Find("G3") && s0.Print("G3") == "125");
    assert("Invalid sheet contents" && s0.Find("G4") && s0.Print("G4") == "17");
    assert("Invalid sheet contents" && s0.Find("F1") && s0.Print("F1") == "=G3+G4");
    assert("Invalid sheet contents" && s0.Find("B4") && s0.Print("B4") == "=F1");
    assert("Invalid sheet contents" && s0.Find("D8") && s0.Print("D8") == "=5+8");
    assert("Invalid sheet contents" && s0.Find("B1") && s0.Print("B1") == "=D8+7");
    assert("Invalid sheet contents" && s0.Find("C2") && s0.Print("C2") == "=1/2");
    assert("Invalid sheet contents" && s0.Find("B2") && s0.Print("B2") == "=C2*2");
    assert("Invalid sheet contents" && s0.Find("A3") && s0.Print("A3") == "=B2");
    assert("Invalid sheet contents" && s0.Find("A1") && s0.Print("A1") == "=A2+A3+B1+B4");
    assert("Invalid sheet contents" && s0.Find("D9") && s0.Print("D9") == "=A1+5");
    assert("Invalid sheet contents" && s0.Find("C9") && s0.Print("C9") == "=D9-5");
    assert("Invalid sheet contents" && s0.Find("A4") && s0.Print("A4") == "Sum:");
    assert("Invalid sheet contents" && s0.Find("C10") && s0.Print("C10") == "Total:");
    assert("Invalid sheet contents" && s0.Find("D10") && s0.Print("D10") == "=D7");

    /**
     * Check if file containing cell cycle doesn't get loaded
     * test2.txt has cycle caused by cell D5 = C9
     */
     assert("Loaded file containing cycle" && ! s0.LoadFromFile("test2.txt"));

    /**
     * Check if corrupt file doesn't get loaded
     * test3.txt has corrupt data at line 1
     */
     assert("Loaded corrupt file" && ! s0.LoadFromFile("test3.txt"));

     /**
      * Check if invalid format gets rejected
      * test4.txt is of invalid format
      */
      assert("Loaded file with invalid format" && ! s0.LoadFromFile("test4.txt"));
}

void TestCycleDetection() {

    /*                           --> B1
     *                           |
     *                  --> A3 -- > B3
     *                  |
     *            C2--> A2 --> A4 --> D1
     *                  |
     *    G2 -->  F3 <-- --> A5
     */

    CLinks l0;
    set <string> emptySet;

    l0.Set("B1", emptySet);
    l0.Set("B3", emptySet);
    l0.Set("D1", emptySet);
    l0.Set("A5", emptySet);
    l0.Set("F3", emptySet);
    l0.Set("A3", set < string > {"B1", "B3"});
    l0.Set("A4", set < string > {"D1"});
    l0.Set("A2", set < string > {"A3", "A4", "A5", "F3"});
    l0.Set("G2", set < string > {"F3"});
    l0.Set("C2", set < string > {"A2"});

    assert("Cycle not detected as expected" && !l0.IsCyclic());

    l0.Set("B1", set < string > {"C2"});
    assert("Cycle not detected as expected" && l0.IsCyclic());
    l0.Set("B1", emptySet);

    l0.Set("D1", set < string > {"A4"});
    assert("Cycle not detected as expected" && l0.IsCyclic());
    l0.Set("D1", emptySet);

    l0.Set("B3", set < string > {"B3"});
    assert("Cycle not detected as expected" && l0.IsCyclic());
    l0.Set("B3", emptySet);

    assert("Link not set as expected" && ! l0.SafeSet("B1", set < string > {"C2"}));
    assert("Link not set as expected" && ! l0.SafeSet("D1", set < string > {"A4"}));
    assert("Link not set as expected" && ! l0.SafeSet("B3", set < string > {"B3"}));

    assert("Link not set as expected" && l0.SafeSet("A1", set < string > {"B1", "B3"}));
    assert("Link not set as expected" && l0.SafeSet("A2", set < string > {"A3", "B1"}));
    assert("Link not set as expected" && l0.SafeSet("A1", set < string > {"F3", "A5"}));
}

void TestCSheet() {

    TestSetAndDelete();
    TestLoadingFromFile();
    TestCycleDetection();
}
