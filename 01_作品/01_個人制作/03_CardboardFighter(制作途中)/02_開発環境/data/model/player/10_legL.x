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
 0.04346;-0.43768;-3.66961;,
 0.04346;-19.08875;-2.93189;,
 -2.74579;-19.08875;0.00000;,
 -3.41297;-0.43768;0.00000;,
 0.04346;-19.08875;2.93189;,
 0.04346;-0.43768;3.66961;,
 2.83270;-19.08875;-0.00000;,
 3.49989;-0.43768;-0.00000;,
 0.04346;-19.08875;-2.93189;,
 0.04346;-0.43768;-3.66961;,
 0.04346;3.22393;0.00000;,
 0.04346;3.22393;0.00000;,
 0.04346;3.22393;0.00000;,
 0.04346;3.22393;0.00000;,
 0.04346;-20.64347;-0.00000;,
 0.04346;-20.64347;-0.00000;,
 0.04346;-20.64347;-0.00000;,
 0.04346;-20.64347;-0.00000;;
 
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
  0,
  0,
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
  14;
  -0.599948;0.566330;-0.565095;,
  -0.697104;0.283812;-0.658405;,
  -0.697104;0.283812;0.658405;,
  0.697105;0.283811;0.658404;,
  -0.646647;-0.453573;-0.613285;,
  -0.646647;-0.453573;0.613285;,
  0.646649;-0.453573;0.613284;,
  -0.486873;-0.873473;0.000000;,
  0.697105;0.283811;-0.658404;,
  0.646649;-0.453573;-0.613284;,
  -0.599948;0.566330;0.565095;,
  0.599949;0.566329;0.565095;,
  0.599949;0.566329;-0.565095;,
  0.486875;-0.873472;-0.000000;;
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
  3;7,5,5;,
  3;13,6,6;,
  3;13,9,9;;
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
