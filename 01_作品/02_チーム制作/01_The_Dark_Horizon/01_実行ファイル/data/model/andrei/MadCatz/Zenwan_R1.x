xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 52;
 -6.53107;-0.17343;6.73690;,
 -6.53107;-10.73735;6.73690;,
 0.11224;-10.73735;6.73690;,
 0.11224;-0.17343;6.73690;,
 0.11224;-0.17343;6.73690;,
 0.11224;-10.73735;6.73690;,
 6.75551;-10.73735;6.73690;,
 6.75551;-0.17343;6.73690;,
 6.75551;-10.73735;0.09363;,
 6.75551;-0.17343;0.09363;,
 6.75551;-0.17343;0.09363;,
 6.75551;-10.73735;0.09363;,
 6.75551;-10.73735;-6.54964;,
 6.75551;-0.17343;-6.54964;,
 0.11224;-10.73735;-6.54964;,
 0.11224;-0.17343;-6.54964;,
 -6.53107;-10.73735;-6.54964;,
 -6.53107;-0.17343;-6.54964;,
 -6.53107;-10.73735;0.09363;,
 -6.53107;-0.17343;0.09363;,
 -6.53107;-0.17343;0.09363;,
 -6.53107;-10.73735;0.09363;,
 -6.53107;-0.17343;6.73690;,
 6.75551;-0.17343;6.73690;,
 6.75551;-10.73735;6.73690;,
 -6.53107;-10.73735;6.73690;,
 -6.53107;-10.73735;6.73690;,
 -6.53107;-23.75295;6.73690;,
 0.11224;-23.75295;6.73690;,
 0.11224;-10.73735;6.73690;,
 0.11224;-10.73735;6.73690;,
 0.11224;-23.75295;6.73690;,
 6.75551;-23.75295;6.73690;,
 6.75551;-10.73735;6.73690;,
 6.75551;-23.75295;0.09363;,
 6.75551;-10.73735;0.09363;,
 6.75551;-10.73735;0.09363;,
 6.75551;-23.75295;0.09363;,
 6.75551;-23.75295;-6.54964;,
 6.75551;-10.73735;-6.54964;,
 0.11224;-23.75295;-6.54964;,
 0.11224;-10.73735;-6.54964;,
 -6.53107;-23.75295;-6.54964;,
 -6.53107;-10.73735;-6.54964;,
 -6.53107;-23.75295;0.09363;,
 -6.53107;-10.73735;0.09363;,
 -6.53107;-10.73735;0.09363;,
 -6.53107;-23.75295;0.09363;,
 -6.53107;-10.73735;6.73690;,
 6.75551;-10.73735;6.73690;,
 6.75551;-23.75295;6.73690;,
 -6.53107;-23.75295;6.73690;;
 
 20;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;7,6,8,9;,
 4;10,11,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;20,21,1,0;,
 4;13,17,22,23;,
 4;24,25,16,12;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;33,32,34,35;,
 4;36,37,38,39;,
 4;39,38,40,41;,
 4;41,40,42,43;,
 4;43,42,44,45;,
 4;46,47,27,26;,
 4;39,43,48,49;,
 4;38,50,51,42;;
 
 MeshMaterialList {
  8;
  20;
  1,
  2,
  2,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  1,
  2,
  2,
  0,
  0,
  0,
  0,
  1,
  0,
  0;;
  Material {
   0.392000;0.392000;0.392000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\texture\\andrei\\stainless-steel.jpg";
   }
  }
  Material {
   0.081600;0.109600;0.119200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\texture\\andrei\\Chamber.jpg";
   }
  }
  Material {
   0.269600;0.125600;0.084800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\texture\\andrei\\Chamber.jpg";
   }
  }
  Material {
   0.800000;0.633600;0.360800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\texture\\andrei\\Code.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.200800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  6;
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  20;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  52;
  -0.027644;0.504968;,
  -0.027644;1.137054;,
  0.028848;1.137054;,
  0.028848;0.504968;,
  0.501375;0.546416;,
  0.501375;0.764893;,
  0.582757;0.764893;,
  0.582757;0.546416;,
  0.582757;0.764893;,
  0.582757;0.546416;,
  0.528039;0.815826;,
  0.528039;0.889849;,
  0.528039;0.889849;,
  0.528039;0.815826;,
  0.500466;0.889849;,
  0.500466;0.815826;,
  0.472892;0.889849;,
  0.472892;0.815826;,
  0.472892;0.889849;,
  0.472892;0.815826;,
  0.152774;0.504968;,
  0.152774;1.137054;,
  0.472892;0.815826;,
  0.528039;0.815826;,
  0.528039;0.889849;,
  0.472892;0.889849;,
  -0.027644;1.137054;,
  -0.027644;1.915834;,
  0.028848;1.915834;,
  0.028848;1.137054;,
  0.501375;0.764893;,
  0.501375;1.034073;,
  0.582757;1.034073;,
  0.582757;0.764893;,
  0.582757;1.034073;,
  0.582757;0.764893;,
  0.528039;0.889849;,
  0.528039;0.981052;,
  0.528039;0.981052;,
  0.528039;0.889849;,
  0.500466;0.981052;,
  0.500466;0.889849;,
  0.472892;0.981052;,
  0.472892;0.889849;,
  0.472892;0.981052;,
  0.472892;0.889849;,
  0.152774;1.137054;,
  0.152774;1.915834;,
  0.472892;0.889849;,
  0.528039;0.889849;,
  0.528039;0.981052;,
  0.472892;0.981052;;
 }
}
