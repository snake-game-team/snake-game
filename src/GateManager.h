#pragma once
#include "Gate.h"
#include "Map.h"
#include "Snake.h"
#include <vector>
#include <cstdlib>

class GateManager {
private:
    Gate gate1;
    Gate gate2;
    bool gateActive = false;
    int gateUseCount = 0; // 게이트 사용 횟수 카운트
public:
    void createGates(Map& map) {
        std::vector<std::pair<int, int>> wallPositions;

        // Wall 목록 수집
        for (int y = 0; y < 21; ++y) {
            for (int x = 0; x < 39; ++x) {
                char ch = map.getChar(y, x);
                if (ch == '*') { // 일반 Wall만 가능
                    wallPositions.push_back({y, x});
                }
            }
        }

        if (wallPositions.size() < 2) return;

        // 무작위로 두 개 선택
        auto pos1 = wallPositions[rand() % wallPositions.size()];
        auto pos2 = wallPositions[rand() % wallPositions.size()];
        while (pos1 == pos2) {
            pos2 = wallPositions[rand() % wallPositions.size()];
        }

        gate1.setPosition(pos1.first, pos1.second);
        gate2.setPosition(pos2.first, pos2.second);

        // 맵에 표시
        map.addChar(pos1.first, pos1.second, '█');
        map.addChar(pos2.first, pos2.second, '█');
        gateActive = true;
    }

    bool isGate(int y, int x) const {
        return gate1.isAt(y, x) || gate2.isAt(y, x);
    }

    // 진입 Gate → 진출 Gate 반환
    std::pair<Gate, Gate> getGatePair(int y, int x) const {
        if (gate1.isAt(y, x)) {
            return {gate1, gate2};
        } else if (gate2.isAt(y, x)) {
            return {gate2, gate1};
        }
        return {Gate(), Gate()};
    }

    bool isActive() const {
        return gateActive;
    }

    const Gate& getGate1() const { 
        return gate1; 
    }

    const Gate& getGate2() const {
        return gate2; 
    }

    // 게이트 사용 시 호출
    void incrementGateUse() {
        gateUseCount++;
    }

    int getGateUseCount() const {
        return gateUseCount;
    }
};
