<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="frames" urn="urn:adsk.eagle:library:229">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="A3L-LOC" urn="urn:adsk.eagle:symbol:13881/1" library_version="1">
<wire x1="288.29" y1="3.81" x2="342.265" y2="3.81" width="0.1016" layer="94"/>
<wire x1="342.265" y1="3.81" x2="373.38" y2="3.81" width="0.1016" layer="94"/>
<wire x1="373.38" y1="3.81" x2="383.54" y2="3.81" width="0.1016" layer="94"/>
<wire x1="383.54" y1="3.81" x2="383.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="383.54" y1="8.89" x2="383.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="383.54" y1="13.97" x2="383.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="383.54" y1="19.05" x2="383.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="288.29" y1="3.81" x2="288.29" y2="24.13" width="0.1016" layer="94"/>
<wire x1="288.29" y1="24.13" x2="342.265" y2="24.13" width="0.1016" layer="94"/>
<wire x1="342.265" y1="24.13" x2="383.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="373.38" y1="3.81" x2="373.38" y2="8.89" width="0.1016" layer="94"/>
<wire x1="373.38" y1="8.89" x2="383.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="373.38" y1="8.89" x2="342.265" y2="8.89" width="0.1016" layer="94"/>
<wire x1="342.265" y1="8.89" x2="342.265" y2="3.81" width="0.1016" layer="94"/>
<wire x1="342.265" y1="8.89" x2="342.265" y2="13.97" width="0.1016" layer="94"/>
<wire x1="342.265" y1="13.97" x2="383.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="342.265" y1="13.97" x2="342.265" y2="19.05" width="0.1016" layer="94"/>
<wire x1="342.265" y1="19.05" x2="383.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="342.265" y1="19.05" x2="342.265" y2="24.13" width="0.1016" layer="94"/>
<text x="344.17" y="15.24" size="2.54" layer="94">&gt;DRAWING_NAME</text>
<text x="344.17" y="10.16" size="2.286" layer="94">&gt;LAST_DATE_TIME</text>
<text x="357.505" y="5.08" size="2.54" layer="94">&gt;SHEET</text>
<text x="343.916" y="4.953" size="2.54" layer="94">Sheet:</text>
<frame x1="0" y1="0" x2="387.35" y2="260.35" columns="8" rows="5" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="A3L-LOC" urn="urn:adsk.eagle:component:13942/1" prefix="FRAME" uservalue="yes" library_version="1">
<description>&lt;b&gt;FRAME&lt;/b&gt;&lt;p&gt;
DIN A3, landscape with location and doc. field</description>
<gates>
<gate name="G$1" symbol="A3L-LOC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="wirepad" urn="urn:adsk.eagle:library:412">
<description>&lt;b&gt;Single Pads&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="SMD1,27-2,54" urn="urn:adsk.eagle:footprint:30822/1" library_version="2">
<description>&lt;b&gt;SMD PAD&lt;/b&gt;</description>
<smd name="1" x="0" y="0" dx="1.27" dy="2.54" layer="1"/>
<text x="0" y="0" size="0.0254" layer="27">&gt;VALUE</text>
<text x="-0.8" y="-2.4" size="1.27" layer="25" rot="R90">&gt;NAME</text>
</package>
</packages>
<packages3d>
<package3d name="SMD1,27-2,54" urn="urn:adsk.eagle:package:30839/1" type="box" library_version="2">
<description>SMD PAD</description>
<packageinstances>
<packageinstance name="SMD1,27-2,54"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="PAD" urn="urn:adsk.eagle:symbol:30808/1" library_version="2">
<wire x1="-1.016" y1="1.016" x2="1.016" y2="-1.016" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-1.016" x2="1.016" y2="1.016" width="0.254" layer="94"/>
<text x="-1.143" y="1.8542" size="1.778" layer="95">&gt;NAME</text>
<text x="-1.143" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="P" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="SMD2" urn="urn:adsk.eagle:component:30857/2" prefix="PAD" uservalue="yes" library_version="2">
<description>&lt;b&gt;SMD PAD&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="PAD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SMD1,27-2,54">
<connects>
<connect gate="1" pin="P" pad="1"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:30839/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="15" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="MB1-120-01-X-S-XX-SL-N">
<packages>
<package name="SAMTEC_MB1-120-01-X-S-XX-SL-N">
<wire x1="-13.032" y1="-0.407" x2="13.032" y2="-0.407" width="0.1" layer="51"/>
<wire x1="13.032" y1="-0.407" x2="13.032" y2="-7.647" width="0.1" layer="51"/>
<wire x1="-13.032" y1="-7.647" x2="-13.032" y2="-0.407" width="0.1" layer="51"/>
<wire x1="13.032" y1="-0.407" x2="13.032" y2="-7.647" width="0.2" layer="21"/>
<wire x1="-13.032" y1="-7.647" x2="-13.032" y2="-0.407" width="0.2" layer="21"/>
<wire x1="-13.032" y1="-7.647" x2="13.032" y2="-7.647" width="0.1" layer="51"/>
<wire x1="-9.152" y1="-7.647" x2="9.152" y2="-7.647" width="0.2" layer="21"/>
<wire x1="-13.032" y1="-0.407" x2="-10.16" y2="-0.407" width="0.2" layer="21"/>
<wire x1="13.032" y1="-0.407" x2="10.16" y2="-0.407" width="0.2" layer="21"/>
<wire x1="-13.282" y1="0.975" x2="13.282" y2="0.975" width="0.05" layer="39"/>
<wire x1="13.282" y1="0.975" x2="13.282" y2="-7.897" width="0.05" layer="39"/>
<wire x1="13.282" y1="-7.897" x2="-13.282" y2="-7.897" width="0.05" layer="39"/>
<wire x1="-13.282" y1="-7.897" x2="-13.282" y2="0.975" width="0.05" layer="39"/>
<text x="-13" y="1.5" size="1.27" layer="25">&gt;NAME</text>
<text x="-13" y="-8.374" size="1.27" layer="27" align="top-left">&gt;VALUE</text>
<circle x="9.5" y="1.5" radius="0.1" width="0.2" layer="21"/>
<circle x="9.5" y="1.5" radius="0.1" width="0.2" layer="51"/>
<polygon width="0.01" layer="31">
<vertex x="11.42" y="-4.191" curve="18.6094"/>
<vertex x="11.2168" y="-4.22423125"/>
<vertex x="10.4027" y="-2.42946875" curve="-23.3177"/>
<vertex x="11.42" y="-2.2225"/>
</polygon>
<polygon width="0.01" layer="31">
<vertex x="10.8148" y="-5.01868125"/>
<vertex x="9.00608125" y="-5.801290625" curve="-43.9993"/>
<vertex x="9.00608125" y="-3.850709375"/>
<vertex x="10.8148" y="-4.63331875" curve="35.1412"/>
</polygon>
<polygon width="0.01" layer="31">
<vertex x="11.1012" y="-4.276740625"/>
<vertex x="10.288" y="-2.4845" curve="39.3504"/>
<vertex x="9.05546875" y="-3.73473125"/>
<vertex x="10.8652" y="-4.51678125" curve="-30.6317"/>
</polygon>
<polygon width="0.01" layer="31">
<vertex x="11.42" y="-5.461" curve="-18.6094"/>
<vertex x="11.2168" y="-5.42776875"/>
<vertex x="10.4027" y="-7.22253125" curve="23.3177"/>
<vertex x="11.42" y="-7.4295"/>
</polygon>
<polygon width="0.01" layer="31">
<vertex x="11.1012" y="-5.375259375"/>
<vertex x="10.288" y="-7.1675" curve="-39.3504"/>
<vertex x="9.05546875" y="-5.91726875"/>
<vertex x="10.8652" y="-5.13521875" curve="30.6317"/>
</polygon>
<polygon width="0.01" layer="31">
<vertex x="11.5744" y="-5.701490625"/>
<vertex x="11.5303" y="-5.45135" curve="80.0127"/>
<vertex x="12.055" y="-4.826" curve="80.1715"/>
<vertex x="11.5303" y="-4.20065"/>
<vertex x="11.5744" y="-3.950509375" curve="-80.0332"/>
<vertex x="12.309" y="-4.826" curve="-80.0049"/>
</polygon>
<polygon width="0.01" layer="1">
<vertex x="11.42" y="-5.677"/>
<vertex x="11.42" y="-7.112"/>
<vertex x="11.293" y="-7.112"/>
<vertex x="11.293" y="-5.836" curve="-11.6879"/>
<vertex x="11.0581" y="-5.77748125"/>
<vertex x="10.5335" y="-6.93405"/>
<vertex x="10.4178" y="-6.881590625"/>
<vertex x="10.9425" y="-5.72501875" curve="-12.1502"/>
<vertex x="10.7465" y="-5.58931875"/>
<vertex x="9.848459375" y="-6.487340625"/>
<vertex x="9.758659375" y="-6.397540625"/>
<vertex x="10.6567" y="-5.49951875"/>
<vertex x="10.5128" y="-5.28776875"/>
<vertex x="9.347240625" y="-5.79215"/>
<vertex x="9.2968" y="-5.6756"/>
<vertex x="10.4624" y="-5.17121875"/>
<vertex x="10.404" y="-4.8895"/>
<vertex x="9.134" y="-4.8895"/>
<vertex x="9.134" y="-4.7625"/>
<vertex x="10.404" y="-4.7625"/>
<vertex x="10.4623" y="-4.48078125"/>
<vertex x="9.2968" y="-3.9764"/>
<vertex x="9.347240625" y="-3.85985"/>
<vertex x="10.5128" y="-4.36423125"/>
<vertex x="10.6567" y="-4.15248125"/>
<vertex x="9.75865" y="-3.254459375"/>
<vertex x="9.848459375" y="-3.16465"/>
<vertex x="10.7465" y="-4.06268125"/>
<vertex x="10.9425" y="-3.92698125"/>
<vertex x="10.4178" y="-2.770409375"/>
<vertex x="10.5335" y="-2.71795"/>
<vertex x="11.0581" y="-3.87451875"/>
<vertex x="11.293" y="-3.816"/>
<vertex x="11.293" y="-2.54"/>
<vertex x="11.42" y="-2.54"/>
<vertex x="11.42" y="-3.975" curve="-90"/>
<vertex x="12.271" y="-4.826" curve="-90"/>
</polygon>
<polygon width="0.01" layer="29">
<vertex x="11.47" y="-5.727"/>
<vertex x="11.47" y="-7.162"/>
<vertex x="11.243" y="-7.162"/>
<vertex x="11.243" y="-5.877" curve="-11.6879"/>
<vertex x="11.0855" y="-5.838209375"/>
<vertex x="10.5584" y="-7.000240625"/>
<vertex x="10.3516" y="-6.90646875"/>
<vertex x="10.8788" y="-5.74443125"/>
<vertex x="10.7507" y="-5.65578125"/>
<vertex x="9.848459375" y="-6.55805"/>
<vertex x="9.68795" y="-6.397540625"/>
<vertex x="10.5902" y="-5.49526875"/>
<vertex x="10.4923" y="-5.35113125"/>
<vertex x="9.321209375" y="-5.8579"/>
<vertex x="9.231059375" y="-5.64956875"/>
<vertex x="10.4021" y="-5.142809375"/>
<vertex x="10.36" y="-4.9395"/>
<vertex x="9.084" y="-4.9395"/>
<vertex x="9.084" y="-4.7125"/>
<vertex x="10.36" y="-4.7125"/>
<vertex x="10.4021" y="-4.509190625"/>
<vertex x="9.23105" y="-4.00243125"/>
<vertex x="9.321209375" y="-3.7941"/>
<vertex x="10.4923" y="-4.300859375"/>
<vertex x="10.5902" y="-4.15671875"/>
<vertex x="9.687940625" y="-3.254459375"/>
<vertex x="9.848459375" y="-3.093940625"/>
<vertex x="10.7507" y="-3.996209375"/>
<vertex x="10.8788" y="-3.90756875"/>
<vertex x="10.3516" y="-2.74553125"/>
<vertex x="10.5584" y="-2.651759375"/>
<vertex x="11.0855" y="-3.813790625"/>
<vertex x="11.243" y="-3.775"/>
<vertex x="11.243" y="-2.49"/>
<vertex x="11.47" y="-2.49"/>
<vertex x="11.47" y="-3.925" curve="-86.6022"/>
<vertex x="12.321" y="-4.826" curve="-86.6251"/>
</polygon>
<polygon width="0.01" layer="31">
<vertex x="-11.42" y="-5.461" curve="18.6094"/>
<vertex x="-11.2168" y="-5.42776875"/>
<vertex x="-10.4027" y="-7.22253125" curve="-23.3177"/>
<vertex x="-11.42" y="-7.4295"/>
</polygon>
<polygon width="0.01" layer="31">
<vertex x="-10.8148" y="-4.63331875"/>
<vertex x="-9.00608125" y="-3.850709375" curve="-43.9993"/>
<vertex x="-9.00608125" y="-5.801290625"/>
<vertex x="-10.8148" y="-5.01868125" curve="35.1412"/>
</polygon>
<polygon width="0.01" layer="31">
<vertex x="-11.1012" y="-5.375259375"/>
<vertex x="-10.288" y="-7.1675" curve="39.3504"/>
<vertex x="-9.05546875" y="-5.91726875"/>
<vertex x="-10.8652" y="-5.13521875" curve="-30.6317"/>
</polygon>
<polygon width="0.01" layer="31">
<vertex x="-11.42" y="-4.191" curve="-18.6094"/>
<vertex x="-11.2168" y="-4.22423125"/>
<vertex x="-10.4027" y="-2.42946875" curve="23.3177"/>
<vertex x="-11.42" y="-2.2225"/>
</polygon>
<polygon width="0.01" layer="31">
<vertex x="-11.1012" y="-4.276740625"/>
<vertex x="-10.288" y="-2.4845" curve="-39.3504"/>
<vertex x="-9.05546875" y="-3.73473125"/>
<vertex x="-10.8652" y="-4.51678125" curve="30.6317"/>
</polygon>
<polygon width="0.01" layer="31">
<vertex x="-11.5744" y="-3.950509375"/>
<vertex x="-11.5303" y="-4.20065" curve="80.0127"/>
<vertex x="-12.055" y="-4.826" curve="80.1715"/>
<vertex x="-11.5303" y="-5.45135"/>
<vertex x="-11.5744" y="-5.701490625" curve="-80.0332"/>
<vertex x="-12.309" y="-4.826" curve="-80.0049"/>
</polygon>
<polygon width="0.01" layer="1">
<vertex x="-11.42" y="-3.975"/>
<vertex x="-11.42" y="-2.54"/>
<vertex x="-11.293" y="-2.54"/>
<vertex x="-11.293" y="-3.816" curve="-11.6879"/>
<vertex x="-11.0581" y="-3.87451875"/>
<vertex x="-10.5335" y="-2.71795"/>
<vertex x="-10.4178" y="-2.770409375"/>
<vertex x="-10.9425" y="-3.92698125" curve="-12.1502"/>
<vertex x="-10.7465" y="-4.06268125"/>
<vertex x="-9.848459375" y="-3.164659375"/>
<vertex x="-9.758659375" y="-3.254459375"/>
<vertex x="-10.6567" y="-4.15248125"/>
<vertex x="-10.5128" y="-4.36423125"/>
<vertex x="-9.347240625" y="-3.85985"/>
<vertex x="-9.2968" y="-3.9764"/>
<vertex x="-10.4624" y="-4.48078125"/>
<vertex x="-10.404" y="-4.7625"/>
<vertex x="-9.134" y="-4.7625"/>
<vertex x="-9.134" y="-4.8895"/>
<vertex x="-10.404" y="-4.8895"/>
<vertex x="-10.4623" y="-5.17121875"/>
<vertex x="-9.2968" y="-5.6756"/>
<vertex x="-9.347240625" y="-5.79215"/>
<vertex x="-10.5128" y="-5.28776875"/>
<vertex x="-10.6567" y="-5.49951875"/>
<vertex x="-9.75865" y="-6.397540625"/>
<vertex x="-9.848459375" y="-6.48735"/>
<vertex x="-10.7465" y="-5.58931875"/>
<vertex x="-10.9425" y="-5.72501875"/>
<vertex x="-10.4178" y="-6.881590625"/>
<vertex x="-10.5335" y="-6.93405"/>
<vertex x="-11.0581" y="-5.77748125"/>
<vertex x="-11.293" y="-5.836"/>
<vertex x="-11.293" y="-7.112"/>
<vertex x="-11.42" y="-7.112"/>
<vertex x="-11.42" y="-5.677" curve="-90"/>
<vertex x="-12.271" y="-4.826" curve="-90"/>
</polygon>
<polygon width="0.01" layer="29">
<vertex x="-11.47" y="-3.925"/>
<vertex x="-11.47" y="-2.49"/>
<vertex x="-11.243" y="-2.49"/>
<vertex x="-11.243" y="-3.775" curve="-11.6879"/>
<vertex x="-11.0855" y="-3.813790625"/>
<vertex x="-10.5584" y="-2.651759375"/>
<vertex x="-10.3516" y="-2.74553125"/>
<vertex x="-10.8788" y="-3.90756875"/>
<vertex x="-10.7507" y="-3.99621875"/>
<vertex x="-9.848459375" y="-3.09395"/>
<vertex x="-9.68795" y="-3.254459375"/>
<vertex x="-10.5902" y="-4.15673125"/>
<vertex x="-10.4923" y="-4.30086875"/>
<vertex x="-9.321209375" y="-3.7941"/>
<vertex x="-9.231059375" y="-4.00243125"/>
<vertex x="-10.4021" y="-4.509190625"/>
<vertex x="-10.36" y="-4.7125"/>
<vertex x="-9.084" y="-4.7125"/>
<vertex x="-9.084" y="-4.9395"/>
<vertex x="-10.36" y="-4.9395"/>
<vertex x="-10.4021" y="-5.142809375"/>
<vertex x="-9.23105" y="-5.64956875"/>
<vertex x="-9.321209375" y="-5.8579"/>
<vertex x="-10.4923" y="-5.351140625"/>
<vertex x="-10.5902" y="-5.49528125"/>
<vertex x="-9.687940625" y="-6.397540625"/>
<vertex x="-9.848459375" y="-6.558059375"/>
<vertex x="-10.7507" y="-5.655790625"/>
<vertex x="-10.8788" y="-5.74443125"/>
<vertex x="-10.3516" y="-6.90646875"/>
<vertex x="-10.5584" y="-7.000240625"/>
<vertex x="-11.0855" y="-5.838209375"/>
<vertex x="-11.243" y="-5.877"/>
<vertex x="-11.243" y="-7.162"/>
<vertex x="-11.47" y="-7.162"/>
<vertex x="-11.47" y="-5.727" curve="-86.6022"/>
<vertex x="-12.321" y="-4.826" curve="-86.6251"/>
</polygon>
<smd name="01" x="9.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="02" x="8.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="03" x="7.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="04" x="6.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="05" x="5.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="06" x="4.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="07" x="3.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="08" x="2.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="09" x="1.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="10" x="0.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="11" x="-0.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="12" x="-1.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="13" x="-2.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="14" x="-3.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="15" x="-4.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="16" x="-5.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="17" x="-6.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="18" x="-7.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="19" x="-8.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<smd name="20" x="-9.5" y="0" dx="0.61" dy="1.45" layer="1" rot="R180"/>
<pad name="S1" x="-11.42" y="-4.826" drill="1.422" diameter="1.702"/>
<pad name="S2" x="11.42" y="-4.826" drill="1.422" diameter="1.702"/>
</package>
</packages>
<symbols>
<symbol name="MB1-120-01-X-S-XX-SL-N">
<wire x1="-5.08" y1="25.4" x2="-5.08" y2="-27.94" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-27.94" x2="5.08" y2="-27.94" width="0.254" layer="94"/>
<wire x1="5.08" y1="-27.94" x2="5.08" y2="25.4" width="0.254" layer="94"/>
<wire x1="5.08" y1="25.4" x2="-5.08" y2="25.4" width="0.254" layer="94"/>
<text x="-5.08" y="26.67" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-30.48" size="1.778" layer="96">&gt;VALUE</text>
<pin name="01" x="-10.16" y="22.86" length="middle" direction="pas"/>
<pin name="02" x="-10.16" y="20.32" length="middle" direction="pas"/>
<pin name="03" x="-10.16" y="17.78" length="middle" direction="pas"/>
<pin name="04" x="-10.16" y="15.24" length="middle" direction="pas"/>
<pin name="05" x="-10.16" y="12.7" length="middle" direction="pas"/>
<pin name="06" x="-10.16" y="10.16" length="middle" direction="pas"/>
<pin name="07" x="-10.16" y="7.62" length="middle" direction="pas"/>
<pin name="08" x="-10.16" y="5.08" length="middle" direction="pas"/>
<pin name="09" x="-10.16" y="2.54" length="middle" direction="pas"/>
<pin name="10" x="-10.16" y="0" length="middle" direction="pas"/>
<pin name="11" x="-10.16" y="-2.54" length="middle" direction="pas"/>
<pin name="12" x="-10.16" y="-5.08" length="middle" direction="pas"/>
<pin name="13" x="-10.16" y="-7.62" length="middle" direction="pas"/>
<pin name="14" x="-10.16" y="-10.16" length="middle" direction="pas"/>
<pin name="15" x="-10.16" y="-12.7" length="middle" direction="pas"/>
<pin name="16" x="-10.16" y="-15.24" length="middle" direction="pas"/>
<pin name="17" x="-10.16" y="-17.78" length="middle" direction="pas"/>
<pin name="18" x="-10.16" y="-20.32" length="middle" direction="pas"/>
<pin name="19" x="-10.16" y="-22.86" length="middle" direction="pas"/>
<pin name="20" x="-10.16" y="-25.4" length="middle" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MB1-120-01-X-S-XX-SL-N" prefix="J">
<description>1mm Mini-Card Guide </description>
<gates>
<gate name="G$1" symbol="MB1-120-01-X-S-XX-SL-N" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SAMTEC_MB1-120-01-X-S-XX-SL-N">
<connects>
<connect gate="G$1" pin="01" pad="01"/>
<connect gate="G$1" pin="02" pad="02"/>
<connect gate="G$1" pin="03" pad="03"/>
<connect gate="G$1" pin="04" pad="04"/>
<connect gate="G$1" pin="05" pad="05"/>
<connect gate="G$1" pin="06" pad="06"/>
<connect gate="G$1" pin="07" pad="07"/>
<connect gate="G$1" pin="08" pad="08"/>
<connect gate="G$1" pin="09" pad="09"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="16" pad="16"/>
<connect gate="G$1" pin="17" pad="17"/>
<connect gate="G$1" pin="18" pad="18"/>
<connect gate="G$1" pin="19" pad="19"/>
<connect gate="G$1" pin="20" pad="20"/>
</connects>
<technologies>
<technology name="">
<attribute name="MANUFACTURER" value="Samtec"/>
<attribute name="MAXIMUM_PACKAGE_HEIGHT" value="5.44 mm"/>
<attribute name="PARTREV" value="J"/>
<attribute name="STANDARD" value="Manufacturer Recommendations"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="FRAME1" library="frames" library_urn="urn:adsk.eagle:library:229" deviceset="A3L-LOC" device=""/>
<part name="J1" library="MB1-120-01-X-S-XX-SL-N" deviceset="MB1-120-01-X-S-XX-SL-N" device=""/>
<part name="PAD9" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD2" device="" package3d_urn="urn:adsk.eagle:package:30839/1"/>
<part name="PAD10" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD2" device="" package3d_urn="urn:adsk.eagle:package:30839/1"/>
<part name="PAD11" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD2" device="" package3d_urn="urn:adsk.eagle:package:30839/1"/>
<part name="PAD12" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD2" device="" package3d_urn="urn:adsk.eagle:package:30839/1"/>
<part name="PAD13" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD2" device="" package3d_urn="urn:adsk.eagle:package:30839/1"/>
<part name="PAD14" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD2" device="" package3d_urn="urn:adsk.eagle:package:30839/1"/>
<part name="PAD15" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD2" device="" package3d_urn="urn:adsk.eagle:package:30839/1"/>
<part name="PAD16" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD2" device="" package3d_urn="urn:adsk.eagle:package:30839/1"/>
<part name="PAD17" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD2" device="" package3d_urn="urn:adsk.eagle:package:30839/1"/>
<part name="PAD18" library="wirepad" library_urn="urn:adsk.eagle:library:412" deviceset="SMD2" device="" package3d_urn="urn:adsk.eagle:package:30839/1"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="FRAME1" gate="G$1" x="0" y="0" smashed="yes">
<attribute name="DRAWING_NAME" x="344.17" y="15.24" size="2.54" layer="94"/>
<attribute name="LAST_DATE_TIME" x="344.17" y="10.16" size="2.286" layer="94"/>
<attribute name="SHEET" x="357.505" y="5.08" size="2.54" layer="94"/>
</instance>
<instance part="J1" gate="G$1" x="93.98" y="81.28" smashed="yes" rot="R180">
<attribute name="NAME" x="99.06" y="54.61" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="99.06" y="111.76" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="PAD9" gate="1" x="111.76" y="60.96" smashed="yes" rot="R180">
<attribute name="NAME" x="112.903" y="59.1058" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="112.903" y="64.262" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="PAD10" gate="1" x="111.76" y="66.04" smashed="yes" rot="R180">
<attribute name="NAME" x="112.903" y="64.1858" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="112.903" y="69.342" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="PAD11" gate="1" x="111.76" y="71.12" smashed="yes" rot="R180">
<attribute name="NAME" x="112.903" y="69.2658" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="112.903" y="74.422" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="PAD12" gate="1" x="111.76" y="76.2" smashed="yes" rot="R180">
<attribute name="NAME" x="112.903" y="74.3458" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="112.903" y="79.502" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="PAD13" gate="1" x="111.76" y="81.28" smashed="yes" rot="R180">
<attribute name="NAME" x="112.903" y="79.4258" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="112.903" y="84.582" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="PAD14" gate="1" x="111.76" y="86.36" smashed="yes" rot="R180">
<attribute name="NAME" x="112.903" y="84.5058" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="112.903" y="89.662" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="PAD15" gate="1" x="111.76" y="91.44" smashed="yes" rot="R180">
<attribute name="NAME" x="112.903" y="89.5858" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="112.903" y="94.742" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="PAD16" gate="1" x="111.76" y="96.52" smashed="yes" rot="R180">
<attribute name="NAME" x="112.903" y="94.6658" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="112.903" y="99.822" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="PAD17" gate="1" x="111.76" y="101.6" smashed="yes" rot="R180">
<attribute name="NAME" x="112.903" y="99.7458" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="112.903" y="104.902" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="PAD18" gate="1" x="111.76" y="106.68" smashed="yes" rot="R180">
<attribute name="NAME" x="112.903" y="104.8258" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="112.903" y="109.982" size="1.778" layer="96" rot="R180"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="N$9" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="20"/>
<pinref part="PAD18" gate="1" pin="P"/>
<wire x1="104.14" y1="106.68" x2="109.22" y2="106.68" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="18"/>
<pinref part="PAD17" gate="1" pin="P"/>
<wire x1="104.14" y1="101.6" x2="109.22" y2="101.6" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="16"/>
<pinref part="PAD16" gate="1" pin="P"/>
<wire x1="104.14" y1="96.52" x2="109.22" y2="96.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="14"/>
<pinref part="PAD15" gate="1" pin="P"/>
<wire x1="104.14" y1="91.44" x2="109.22" y2="91.44" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="12"/>
<pinref part="PAD14" gate="1" pin="P"/>
<wire x1="104.14" y1="86.36" x2="109.22" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="10"/>
<pinref part="PAD13" gate="1" pin="P"/>
<wire x1="104.14" y1="81.28" x2="109.22" y2="81.28" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="08"/>
<pinref part="PAD12" gate="1" pin="P"/>
<wire x1="104.14" y1="76.2" x2="109.22" y2="76.2" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="06"/>
<pinref part="PAD11" gate="1" pin="P"/>
<wire x1="104.14" y1="71.12" x2="109.22" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="04"/>
<pinref part="PAD10" gate="1" pin="P"/>
<wire x1="104.14" y1="66.04" x2="109.22" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="02"/>
<pinref part="PAD9" gate="1" pin="P"/>
<wire x1="104.14" y1="60.96" x2="109.22" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
