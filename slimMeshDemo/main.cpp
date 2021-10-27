/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <Windows.h>
#include <vector>

// MeshInfo Struct
struct MeshInfo {
    unsigned int vertexCnt;
    unsigned int vertexStride;
    unsigned int indexCnt;
    unsigned int targetIndexCnt;
};

// SlimMesh API
typedef unsigned int (*SlimMeshFUN)(unsigned int *, const unsigned int *, const float *, MeshInfo, float);

int main()
{
    // Make MeshInfo and Call SlimMesh API
    const unsigned int VERTEX_ELEMENT_CNT = 3;
    const unsigned int EXPECT_INDEX_CNT = 6;
    std::vector<float> oriVertices = { 0, 0, 0, 1, 0, 0, 2, 0, 0, 0.5f, 1, 0, 1.5f, 1, 0 };
    std::vector<unsigned int> oriIndices = { 0, 1, 3, 3, 1, 4, 1, 2, 4 };

    SlimMeshFUN SlimMesh;
    HINSTANCE hdll = LoadLibrary("SlimMesh.dll");
    if (hdll == nullptr) {
        std::cout << "Cannot locate the SlimMesh.dll file" << std::endl;
        return -1;
    }

    SlimMesh = (SlimMeshFUN)GetProcAddress(hdll, "SlimMesh");
    MeshInfo meshInfo;
    meshInfo.indexCnt = static_cast<unsigned int>(oriIndices.size());
    meshInfo.vertexCnt = static_cast<unsigned int>(oriVertices.size()) / VERTEX_ELEMENT_CNT;
    meshInfo.vertexStride = sizeof(float) * VERTEX_ELEMENT_CNT;
    meshInfo.targetIndexCnt = EXPECT_INDEX_CNT;

    float targetError = 1e-2f;
    std::vector<unsigned int> targetIndices(meshInfo.indexCnt);
    int result = SlimMesh(&targetIndices[0], &oriIndices[0], &oriVertices[0], meshInfo, targetError);
    std::cout << "SlimMesh result = " << result << std::endl;

    targetIndices.clear();
    oriVertices.clear();
    oriIndices.clear();
    FreeLibrary(hdll);
    return 0;
}