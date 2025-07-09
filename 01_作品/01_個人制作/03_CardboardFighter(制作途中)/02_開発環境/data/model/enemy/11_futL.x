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
 18;
 0.10981;-1.75874;-3.66961;,
 0.10981;-6.09145;-10.68668;,
 -2.67944;-4.12046;0.00000;,
 -2.22763;-1.75874;0.00000;,
 0.10981;-5.58472;4.46688;,
 0.10981;-1.75874;3.28868;,
 3.39784;-5.65745;-0.00000;,
 3.10309;-1.75874;-0.00000;,
 0.10981;-6.09145;-10.68668;,
 0.10981;-1.75874;-3.66961;,
 0.10981;2.27041;0.00000;,
 0.10981;2.27041;0.00000;,
 0.10981;2.27041;0.00000;,
 0.10981;2.27041;0.00000;,
 0.10981;-5.44664;-0.00000;,
 0.10981;-5.44664;-0.00000;,
 0.10981;-5.44664;-0.00000;,
 0.10981;-5.44664;-0.00000;;
 
 12;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 3;10,0,3;,
 3;11,3,5;,
 3;12,5,7;,
 3;13,7,9;,
 3;14,2,1;,
 3;15,4,2;,
 3;16,6,4;,
 3;17,8,6;;
 
 MeshMaterialList {
  2;
  12;
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.771765;0.661961;0.458039;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  18;
  -0.757600;0.439508;-0.482570;,
  -0.801772;0.386998;-0.455406;,
  -0.880210;0.451917;-0.144917;,
  -0.779523;0.298383;0.550737;,
  0.721889;0.305381;0.620982;,
  -0.841576;0.332380;-0.425761;,
  -0.807202;0.163554;0.567164;,
  0.768603;0.117813;0.628784;,
  -0.251200;-0.967831;0.014212;,
  0.764782;0.386177;-0.515729;,
  0.840843;0.264781;-0.472096;,
  -0.736865;0.427479;0.523729;,
  0.648159;0.481521;0.589939;,
  0.671570;0.498913;-0.547796;,
  -0.429358;-0.903037;0.013263;,
  -0.250809;-0.966279;0.058303;,
  -0.251102;-0.967499;-0.029909;,
  -0.063978;-0.997844;0.014650;;
  12;
  4;1,5,5,2;,
  4;6,6,6,3;,
  4;4,7,7,4;,
  4;9,10,10,9;,
  3;0,1,2;,
  3;11,2,3;,
  3;12,4,4;,
  3;13,9,9;,
  3;8,14,15;,
  3;8,16,14;,
  3;8,17,16;,
  3;8,15,17;;
 }
 MeshTextureCoords {
  18;
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.125000;0.000000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.875000;0.000000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;;
 }
}
