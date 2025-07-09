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
 1.65981;1.22148;-3.00593;,
 18.04249;1.22148;-2.29621;,
 18.04249;-0.48086;-0.00000;,
 1.65981;-1.39265;-0.00000;,
 18.04249;1.22148;2.29621;,
 1.65981;1.22148;3.00593;,
 18.04249;2.92382;0.00000;,
 1.65981;3.83562;0.00000;,
 18.04249;1.22148;-2.29621;,
 1.65981;1.22148;-3.00593;,
 -1.76632;1.22148;0.00000;,
 -1.76632;1.22148;0.00000;,
 -1.76632;1.22148;0.00000;,
 -1.76632;1.22148;0.00000;,
 21.26234;1.22148;0.00000;,
 21.26234;1.22148;0.00000;,
 21.26234;1.22148;0.00000;,
 21.26234;1.22148;0.00000;;
 
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
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
  16;
  -0.498950;-0.653934;-0.568699;,
  -0.241861;-0.745285;-0.621332;,
  -0.241861;-0.745285;0.621332;,
  -0.241862;0.745284;0.621333;,
  0.216090;-0.772398;-0.597249;,
  0.216090;-0.772398;0.597249;,
  0.216091;0.772397;0.597250;,
  0.390918;-0.739392;-0.548163;,
  -0.241862;0.745284;-0.621333;,
  0.216091;0.772397;-0.597250;,
  -0.498950;-0.653934;0.568699;,
  -0.498951;0.653933;0.568700;,
  -0.498951;0.653933;-0.568700;,
  0.390918;-0.739392;0.548163;,
  0.390918;0.739392;0.548163;,
  0.390918;0.739392;-0.548163;;
  12;
  4;1,4,4,1;,
  4;2,5,5,2;,
  4;3,6,6,3;,
  4;8,9,9,8;,
  3;0,1,1;,
  3;10,2,2;,
  3;11,3,3;,
  3;12,8,8;,
  3;7,4,4;,
  3;13,5,5;,
  3;14,6,6;,
  3;15,9,9;;
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
