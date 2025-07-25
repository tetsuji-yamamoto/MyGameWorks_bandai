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
 36;
 6.00000;0.00000;-6.00000;,
 6.00000;-15.00000;-6.00000;,
 -6.00000;-15.00000;-6.00000;,
 -6.00000;0.00000;-6.00000;,
 -6.00000;0.00000;-6.00000;,
 -6.00000;-15.00000;-6.00000;,
 -6.00000;-15.00000;6.00000;,
 -6.00000;0.00000;6.00000;,
 -6.00000;0.00000;6.00000;,
 -6.00000;-15.00000;6.00000;,
 6.00000;-15.00000;6.00000;,
 6.00000;0.00000;6.00000;,
 6.00000;0.00000;6.00000;,
 6.00000;-15.00000;6.00000;,
 6.00000;-15.00000;-6.00000;,
 6.00000;0.00000;-6.00000;,
 6.00000;-15.00000;-6.00000;,
 -6.00000;-15.00000;-6.00000;,
 -6.00000;0.00000;6.00000;,
 5.94395;0.00119;5.89502;,
 5.94395;4.24383;4.13766;,
 -6.00000;4.24264;4.24264;,
 5.94394;6.00119;-0.10498;,
 -6.00000;6.00000;-0.00000;,
 5.94395;4.24383;-4.34762;,
 -6.00000;4.24264;-4.24264;,
 5.94395;0.00119;-6.10498;,
 -6.00000;0.00000;-6.00000;,
 -6.00000;0.00000;0.00000;,
 -6.00000;0.00000;0.00000;,
 -6.00000;0.00000;0.00000;,
 -6.00000;0.00000;0.00000;,
 5.94395;0.00119;-0.10498;,
 5.94395;0.00119;-0.10498;,
 5.94395;0.00119;-0.10498;,
 5.94395;0.00119;-0.10498;;
 
 17;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,13,6,17;,
 4;18,19,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 4;25,24,26,27;,
 3;28,18,21;,
 3;29,21,23;,
 3;30,23,25;,
 3;31,25,27;,
 3;32,20,19;,
 3;33,22,20;,
 3;34,24,22;,
 3;35,26,24;;
 
 MeshMaterialList {
  4;
  17;
  0,
  0,
  0,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.760000;0.211608;0.000000;1.000000;;
   0.000000;
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
   0.800000;0.752941;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  19;
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.000000;1.000000;,
  -1.000000;-0.000000;0.000000;,
  -0.008158;0.382671;-0.923849;,
  0.008082;0.382671;0.923849;,
  0.006144;0.707098;0.707089;,
  -0.000100;1.000000;0.000000;,
  -0.006285;0.707097;-0.707089;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;;
  17;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,4,4;,
  3;3,1,12;,
  3;3,12,13;,
  3;3,13,14;,
  3;3,14,15;,
  3;9,16,10;,
  3;9,17,16;,
  3;9,18,17;,
  3;9,10,18;;
 }
 MeshTextureCoords {
  36;
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
