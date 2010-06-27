<!-- Tufts VUE 2.3.1 concept-map (basicEnemyAI.vue) 2010-06-10 -->
<!-- Tufts VUE: http://vue.tufts.edu/ -->
<!-- Do Not Remove: VUE mapping @version(1.1) jar:file:/C:/Program%20Files%20(x86)/VUE/VUE.jar!/tufts/vue/resources/lw_mapping_1_1.xml -->
<!-- Do Not Remove: Saved date Thu Jun 10 19:30:23 EDT 2010 by Preston Stoll on platform Windows 7 6.1 in JVM 1.6.0_18-b07 -->
<!-- Do Not Remove: Saving version @(#)VUE: built May 6 2009 at 1148 by vue on Linux 2.4.21-57.EL i386 JVM 1.5.0_06-b05 -->
<?xml version="1.0" encoding="US-ASCII"?>
<LW-MAP xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:noNamespaceSchemaLocation="none" ID="0" label="basicEnemyAI.vue"
    x="0.0" y="0.0" width="1.4E-45" height="1.4E-45" strokeWidth="0.0" autoSized="false">
    <resource referenceCreated="1276212623607"
        spec="C:\Users\Preston Stoll\Desktop\Desktop Stuff\cptlog\basicEnemyAI.vue"
        type="1" xsi:type="URLResource">
        <title>basicEnemyAI.vue</title>
        <property key="File" value="C:\Users\Preston Stoll\Desktop\Desktop Stuff\cptlog\basicEnemyAI.vue"/>
    </resource>
    <fillColor>#FFFFFF</fillColor>
    <strokeColor>#404040</strokeColor>
    <textColor>#000000</textColor>
    <font>SansSerif-plain-14</font>
    <metadata-list category-list-size="1" other-list-size="0"
        ontology-list-size="0" RCategoryListSize="0">
        <ontology-list-string></ontology-list-string>
        <metadata xsi:type="vue-metadata-element">
            <value></value>
            <key>http://vue.tufts.edu/vue.rdfs#none</key>
            <type>1</type>
        </metadata>
    </metadata-list>
    <URIString>http://vue.tufts.edu/rdf/resource/243338f9c0a838010027d9e58ff5ea2f</URIString>
    <child ID="8" label="Basic Enemy" layerID="1" x="232.0" y="118.0"
        width="168.0" height="60.0" strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#F2AE45</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338f9c0a838010027d9e51639db25</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="9" label="Find Nearest Player" layerID="1" x="244.0"
        y="226.0" width="142.0" height="66.0" strokeWidth="1.0"
        autoSized="false" xsi:type="node">
        <fillColor>#9DDB53</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fac0a838010027d9e59c470688</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="10" label="Is the player in sight range?" layerID="1"
        x="381.0" y="336.0" width="167.0" height="73.0"
        strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#FEFD8C</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fac0a838010027d9e5c2425638</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="11" label="Is the player in attack range?" layerID="1"
        x="469.0" y="492.0" width="181.0" height="86.0"
        strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#AF55F4</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fac0a838010027d9e58a148d3c</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="12" label="Do nothing" layerID="1" x="614.0" y="284.0"
        width="171.0" height="70.0" strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#82CDE4</fillColor>
        <strokeColor>#000000</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fac0a838010027d9e5e9e4e27f</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="13" label="Move towards player and path around obstacles"
        layerID="1" x="839.0" y="230.0" width="283.0" height="79.0"
        strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#BDE5F2</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fbc0a838010027d9e51ae2f185</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="14" label="Attack" layerID="1" x="250.0" y="730.0"
        width="206.0" height="73.0" strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#EA2218</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fbc0a838010027d9e5c8f7c994</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="15" label="no" layerID="1" x="383.00226" y="173.5"
        width="130.33612" height="56.568405" strokeWidth="1.0"
        autoSized="false" controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fbc0a838010027d9e58668c927</URIString>
        <point1 x="512.8384" y="174.00002"/>
        <point2 x="383.50226" y="229.56842"/>
        <ID1 xsi:type="node">34</ID1>
        <ID2 xsi:type="node">9</ID2>
    </child>
    <child ID="16" layerID="1" x="357.96698" y="291.5" width="58.955933"
        height="45.0" strokeWidth="1.0" autoSized="false"
        controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fcc0a838010027d9e5a543b24a</URIString>
        <point1 x="358.46698" y="292.0"/>
        <point2 x="416.4229" y="336.0"/>
        <ID1 xsi:type="node">9</ID1>
        <ID2 xsi:type="node">10</ID2>
    </child>
    <child ID="17" layerID="1" x="316.97092" y="291.5" width="33.79608"
        height="439.0" strokeWidth="1.0" autoSized="false"
        controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fcc0a838010027d9e53a619cc6</URIString>
        <point1 x="350.267" y="730.0"/>
        <point2 x="317.47092" y="292.0"/>
        <ID1 xsi:type="node">14</ID1>
        <ID2 xsi:type="node">9</ID2>
    </child>
    <child ID="18" label="yes" layerID="1" x="485.33844" y="408.5"
        width="49.52304" height="83.99994" strokeWidth="1.0"
        autoSized="false" controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fcc0a838010027d9e568450819</URIString>
        <point1 x="485.83847" y="409.0"/>
        <point2 x="534.3615" y="491.99994"/>
        <ID1 xsi:type="node">10</ID1>
        <ID2 xsi:type="node">11</ID2>
    </child>
    <child ID="19" label="yes" layerID="1" x="598.669" y="577.5"
        width="60.042236" height="65.0" strokeWidth="1.0"
        autoSized="false" controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fdc0a838010027d9e5fb56cf67</URIString>
        <point1 x="599.169" y="578.0"/>
        <point2 x="658.21124" y="642.0"/>
        <ID1 xsi:type="node">11</ID1>
        <ID2 xsi:type="node">24</ID2>
    </child>
    <child ID="20" label="no" layerID="1" x="627.1846" y="308.5"
        width="291.18073" height="184.0" strokeWidth="1.0"
        autoSized="false" controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fdc0a838010027d9e555f11864</URIString>
        <point1 x="917.8653" y="309.0"/>
        <point2 x="627.6846" y="492.0"/>
        <ID1 xsi:type="node">13</ID1>
        <ID2 xsi:type="node">11</ID2>
    </child>
    <child ID="21" label="no" layerID="1" x="547.5" y="337.9649"
        width="67.0" height="16.025513" strokeWidth="1.0"
        autoSized="false" controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fdc0a838010027d9e52306e47a</URIString>
        <point1 x="548.0" y="353.49042"/>
        <point2 x="614.0" y="338.4649"/>
        <ID1 xsi:type="node">10</ID1>
        <ID2 xsi:type="node">12</ID2>
    </child>
    <child ID="22" layerID="1" x="385.5" y="259.6202" width="454.0"
        height="8.147278" strokeWidth="1.0" autoSized="false"
        controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fdc0a838010027d9e5efdd2e88</URIString>
        <point1 x="839.0" y="267.2675"/>
        <point2 x="386.0" y="260.1202"/>
        <ID1 xsi:type="node">13</ID1>
        <ID2 xsi:type="node">9</ID2>
    </child>
    <child ID="23" layerID="1" x="385.5" y="269.5793" width="229.0"
        height="36.578674" strokeWidth="1.0" autoSized="false"
        controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fec0a838010027d9e527097e51</URIString>
        <point1 x="614.0" y="305.658"/>
        <point2 x="386.0" y="270.0793"/>
        <ID1 xsi:type="node">12</ID1>
        <ID2 xsi:type="node">9</ID2>
    </child>
    <child ID="24" label="Has the Enter Combat dialogue been said?"
        layerID="1" x="564.0" y="642.0" width="253.0" height="70.0"
        strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#30D643</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fec0a838010027d9e5fc6aefda</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="25" label="no" layerID="1" x="586.87024" y="353.5"
        width="90.44452" height="139.00006" strokeWidth="1.0"
        autoSized="false" controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338fec0a838010027d9e5ec1f1135</URIString>
        <point1 x="587.3703" y="492.00006"/>
        <point2 x="676.8148" y="354.0"/>
        <ID1 xsi:type="node">11</ID1>
        <ID2 xsi:type="node">12</ID2>
    </child>
    <child ID="27" label="no" layerID="1" x="749.5664" y="711.5"
        width="55.88617" height="33.25" strokeWidth="1.0"
        autoSized="false" controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338ffc0a838010027d9e55ff15f8d</URIString>
        <point1 x="750.0664" y="712.0"/>
        <point2 x="804.9526" y="744.25"/>
        <ID1 xsi:type="node">24</ID1>
        <ID2 xsi:type="node">31</ID2>
    </child>
    <child ID="28" label="yes" layerID="1" x="455.34393" y="709.07214"
        width="112.828094" height="30.655151" strokeWidth="1.0"
        autoSized="false" controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338ffc0a838010027d9e5684e39b6</URIString>
        <point1 x="567.67206" y="709.57214"/>
        <point2 x="455.84396" y="739.2273"/>
        <ID1 xsi:type="node">24</ID1>
        <ID2 xsi:type="node">14</ID2>
    </child>
    <child ID="29" layerID="1" x="455.49997" y="790.72314"
        width="142.85455" height="35.04944" strokeWidth="1.0"
        autoSized="false" controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/243338ffc0a838010027d9e5aac5589b</URIString>
        <point1 x="597.85455" y="825.2726"/>
        <point2 x="456.0" y="791.22314"/>
        <ID1 xsi:type="node">30</ID1>
        <ID2 xsi:type="node">14</ID2>
    </child>
    <child ID="30" label="Play Enter Combat dialogue" layerID="1"
        x="596.0" y="820.75" width="166.0" height="48.0"
        strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#FEFB03</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333900c0a838010027d9e5be24d6d4</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="31" label="Any voices playing?" layerID="1" x="764.5"
        y="744.25" width="166.0" height="50.0" strokeWidth="1.0"
        autoSized="false" xsi:type="node">
        <fillColor>#33A8F5</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333900c0a838010027d9e52a53581b</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="32" label="no" layerID="1" x="732.06274" y="793.75"
        width="60.142517" height="27.5" strokeWidth="1.0"
        autoSized="false" controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333900c0a838010027d9e53f67817e</URIString>
        <point1 x="791.7053" y="794.25"/>
        <point2 x="732.5628" y="820.75"/>
        <ID1 xsi:type="node">31</ID1>
        <ID2 xsi:type="node">30</ID2>
    </child>
    <child ID="33" label="yes" layerID="1" x="455.5" y="760.93066"
        width="309.5" height="14.0" strokeWidth="1.0" autoSized="false"
        controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333901c0a838010027d9e524ec1df8</URIString>
        <point1 x="764.5" y="768.78845"/>
        <point2 x="456.0" y="767.0728"/>
        <ID1 xsi:type="node">31</ID1>
        <ID2 xsi:type="node">14</ID2>
    </child>
    <child ID="34" label="Is my HP less than zero?" layerID="1"
        x="494.0" y="115.0" width="175.0" height="59.0"
        strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#E8E622</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333901c0a838010027d9e5d08c7e02</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="35" label="Any voices playing?" layerID="1" x="748.0"
        y="69.0" width="189.0" height="52.0" strokeWidth="1.0"
        autoSized="false" xsi:type="node">
        <fillColor>#33A8F5</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333901c0a838010027d9e53c812cc0</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="36" label="Play On Death dialogue" layerID="1" x="1011.0"
        y="112.0" width="169.0" height="51.0" strokeWidth="1.0"
        autoSized="false" xsi:type="node">
        <fillColor>#DAA9FF</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333902c0a838010027d9e56ec9091b</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="37" label="yes" layerID="1" x="668.5" y="112.35152"
        width="80.37378" height="16.053658" strokeWidth="1.0"
        autoSized="false" controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333902c0a838010027d9e5566a8c7b</URIString>
        <point1 x="669.0" y="127.905174"/>
        <point2 x="748.3738" y="112.85152"/>
        <ID1 xsi:type="node">34</ID1>
        <ID2 xsi:type="node">35</ID2>
    </child>
    <child ID="38" label="no" layerID="1" x="936.5" y="110.08993"
        width="75.0" height="14.0" strokeWidth="1.0" autoSized="false"
        controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333902c0a838010027d9e595157809</URIString>
        <point1 x="937.0" y="110.87451"/>
        <point2 x="1011.0" y="123.30534"/>
        <ID1 xsi:type="node">35</ID1>
        <ID2 xsi:type="node">36</ID2>
    </child>
    <child ID="39" label="Wait for dialogue to stop" layerID="1"
        x="760.0" y="149.0" width="169.0" height="48.0"
        strokeWidth="1.0" autoSized="false" xsi:type="node">
        <fillColor>#9DDB53</fillColor>
        <strokeColor>#776D6D</strokeColor>
        <textColor>#000000</textColor>
        <font>Arial-bold-12</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333902c0a838010027d9e5498ad9cf</URIString>
        <shape arcwidth="20.0" archeight="20.0" xsi:type="roundRect"/>
    </child>
    <child ID="40" label="yes" layerID="1" x="834.02563" y="120.5"
        width="19.0" height="29.0" strokeWidth="1.0" autoSized="false"
        controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333903c0a838010027d9e56161b572</URIString>
        <point1 x="843.1667" y="121.0"/>
        <point2 x="843.88464" y="149.0"/>
        <ID1 xsi:type="node">35</ID1>
        <ID2 xsi:type="node">39</ID2>
    </child>
    <child ID="41" layerID="1" x="928.5" y="148.95119" width="83.0"
        height="12.597595" strokeWidth="1.0" autoSized="false"
        controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333903c0a838010027d9e52e06974b</URIString>
        <point1 x="929.0" y="161.04878"/>
        <point2 x="1011.0" y="149.45119"/>
        <ID1 xsi:type="node">39</ID1>
        <ID2 xsi:type="node">36</ID2>
    </child>
    <child ID="42" layerID="1" x="399.5" y="145.15349" width="95.0"
        height="2.2391663" strokeWidth="1.0" autoSized="false"
        controlCount="0" arrowState="2" xsi:type="link">
        <strokeColor>#404040</strokeColor>
        <textColor>#404040</textColor>
        <font>Arial-plain-11</font>
        <metadata-list category-list-size="1" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
            <metadata xsi:type="vue-metadata-element">
                <value></value>
                <key>http://vue.tufts.edu/vue.rdfs#none</key>
                <type>1</type>
            </metadata>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333903c0a838010027d9e503ee381f</URIString>
        <point1 x="400.0" y="146.89265"/>
        <point2 x="494.0" y="145.65349"/>
        <ID1 xsi:type="node">8</ID1>
        <ID2 xsi:type="node">34</ID2>
    </child>
    <layer ID="1" label="Layer 1" x="0.0" y="0.0" width="1.4E-45"
        height="1.4E-45" strokeWidth="0.0" autoSized="false">
        <metadata-list category-list-size="0" other-list-size="0"
            ontology-list-size="0" RCategoryListSize="0">
            <ontology-list-string></ontology-list-string>
        </metadata-list>
        <URIString>http://vue.tufts.edu/rdf/resource/24333904c0a838010027d9e5699afd24</URIString>
    </layer>
    <userZoom>1.0</userZoom>
    <userOrigin x="-12.0" y="-12.0"/>
    <presentationBackground>#202020</presentationBackground>
    <PathwayList currentPathway="0" revealerIndex="-1">
        <pathway ID="0" label="Untitled Pathway" x="0.0" y="0.0"
            width="1.4E-45" height="1.4E-45" strokeWidth="0.0"
            autoSized="false" currentIndex="-1" open="true">
            <strokeColor>#B3993333</strokeColor>
            <textColor>#000000</textColor>
            <font>SansSerif-plain-14</font>
            <metadata-list category-list-size="0" other-list-size="0"
                ontology-list-size="0" RCategoryListSize="0">
                <ontology-list-string></ontology-list-string>
            </metadata-list>
            <URIString>http://vue.tufts.edu/rdf/resource/24333904c0a838010027d9e580a25f00</URIString>
            <masterSlide ID="43" x="0.0" y="0.0" width="800.0"
                height="600.0" locked="true" strokeWidth="0.0" autoSized="false">
                <fillColor>#000000</fillColor>
                <strokeColor>#404040</strokeColor>
                <textColor>#000000</textColor>
                <font>SansSerif-plain-14</font>
                <metadata-list category-list-size="0"
                    other-list-size="0" ontology-list-size="0" RCategoryListSize="0">
                    <ontology-list-string></ontology-list-string>
                </metadata-list>
                <URIString>http://vue.tufts.edu/rdf/resource/2433391dc0a838010027d9e533a8b3fb</URIString>
                <titleStyle ID="44" label="Header" x="335.5" y="172.5"
                    width="129.0" height="55.0" strokeWidth="0.0"
                    autoSized="true" isStyle="true" xsi:type="node">
                    <strokeColor>#404040</strokeColor>
                    <textColor>#FFFFFF</textColor>
                    <font>Gill Sans-plain-36</font>
                    <metadata-list category-list-size="0"
                        other-list-size="0" ontology-list-size="0" RCategoryListSize="0">
                        <ontology-list-string></ontology-list-string>
                    </metadata-list>
                    <URIString>http://vue.tufts.edu/rdf/resource/2433391dc0a838010027d9e5c5c0e517</URIString>
                    <shape xsi:type="rectangle"/>
                </titleStyle>
                <textStyle ID="45" label="Slide Text" x="346.5"
                    y="281.5" width="107.0" height="37.0"
                    strokeWidth="0.0" autoSized="true" isStyle="true" xsi:type="node">
                    <strokeColor>#404040</strokeColor>
                    <textColor>#FFFFFF</textColor>
                    <font>Gill Sans-plain-22</font>
                    <metadata-list category-list-size="0"
                        other-list-size="0" ontology-list-size="0" RCategoryListSize="0">
                        <ontology-list-string></ontology-list-string>
                    </metadata-list>
                    <URIString>http://vue.tufts.edu/rdf/resource/2433391ec0a838010027d9e513efb64b</URIString>
                    <shape xsi:type="rectangle"/>
                </textStyle>
                <linkStyle ID="46" label="Links" x="373.5" y="384.0"
                    width="53.0" height="32.0" strokeWidth="0.0"
                    autoSized="true" isStyle="true" xsi:type="node">
                    <strokeColor>#404040</strokeColor>
                    <textColor>#B3BFE3</textColor>
                    <font>Gill Sans-plain-18</font>
                    <metadata-list category-list-size="0"
                        other-list-size="0" ontology-list-size="0" RCategoryListSize="0">
                        <ontology-list-string></ontology-list-string>
                    </metadata-list>
                    <URIString>http://vue.tufts.edu/rdf/resource/2433391ec0a838010027d9e52c606054</URIString>
                    <shape xsi:type="rectangle"/>
                </linkStyle>
            </masterSlide>
        </pathway>
    </PathwayList>
    <date>2010-06-10</date>
    <mapFilterModel/>
    <modelVersion>5</modelVersion>
    <saveLocation>C:\Users\Preston Stoll\Desktop\Desktop Stuff\cptlog</saveLocation>
    <saveFile>C:\Users\Preston Stoll\Desktop\Desktop Stuff\cptlog\basicEnemyAI.vue</saveFile>
</LW-MAP>
