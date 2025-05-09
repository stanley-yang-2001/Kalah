```mermaid
---
title: Developmental View
--- 
erDiagram


GameDriver ||--o{ GameState: contains
GameDriver ||--o{ GameLogic: contains
GameLogic }|..|{ GameState: manipulate
GameDriver ||--o{ GameBoard: controls
GameBoard ||--o{ Pit: contains
Pit }|..|{ Stone: manipulate
Pit ||--o{circleGenerator: contain



```
