# AHC048 解法戦略

## 問題概要

- K種類のチューブ絵の具で、H=1000種類の目標色を順番に作成
- 20×20のパレット、仕切りで分割・結合可能
- 絵の具1g使用ごとにコストD
- スコア = 1 + D×(使用量-H) + 10^4×色差

## 戦略一覧

### 1. シンプル戦略（ベースライン）

**概要**: 各色を独立ウェルで、最も近いチューブ1本のみ使用

**手順**:

1. 初期仕切りを全て出して全マス独立（400個のウェル）
2. 各目標色に対して最も近いチューブを選択（ユークリッド距離）
3. 1gだけ出して即座に画伯に渡す

**特徴**:

- 実装簡単、確実に動作
- コスト: D×H（最小）
- 精度: 低い（チューブ色との距離そのまま）

### 2. 混色戦略（中級）

**概要**: 2-3本のチューブを混ぜてより正確な色を作成

**手順**:

1. 各目標色に対して最適なチューブの組み合わせを計算
2. 線形計画法orGreedyで最適比率を求解
3. 必要容量分のウェルを用意（2-3マス連結）
4. 計算した比率で絵の具を混合

**特徴**:

- コスト: D×2～3×H
- 精度: 大幅向上
- 計算複雑度: 中程度

### 3. 再利用戦略（上級）

**概要**: 似た色同士でウェルを共有、段階的に目標色へ

**手順**:

1. 目標色をクラスタリング（k-means等）
2. クラスタごとにベース色を作成
3. ウェル分割機能で段階的に調整
4. 複数色で同一ウェルを時系列で再利用

**特徴**:

- コスト: 大幅削減可能
- 精度: 調整次第
- 実装複雑度: 高

### 4. ハイブリッド戦略

**概要**: パラメータDと色分布に応じて戦略を動的選択

**判定基準**:

- D < 100: 混色戦略重視
- D >= 1000: シンプル戦略重視
- 中間: 混合利用

**色分布による調整**:

- 密集した色群: クラスタリング適用
- 散らばった色: 個別対応

## 実装優先度

### Phase 1: ベースライン確立

1. **シンプル戦略**の完全実装
2. 動作確認とスコア測定
3. デバッグ環境整備

### Phase 2: 精度向上

1. **混色戦略**の実装
   - 2本混色から開始
   - 線形計画法による最適化
2. スコア改善効果の測定

### Phase 3: 効率化（時間があれば）

1. **再利用戦略**の部分実装
2. **ハイブリッド戦略**の導入
3. パラメータチューニング

## 技術的検討事項

### 最適化手法

- **2本混色**: (a×C1 + b×C2)/(a+b) = Ctarget を解く
- **3本混色**: 線形計画法 or 全探索
- **クラスタリング**: k-means, DBSCAN等

### 数値計算

- 浮動小数点誤差対策（eps=1e-6）
- ウェル分割時の比率計算精度
- 1g未満判定の厳密処理

### 実装上の注意

- ウェル管理（Union-Find使用）
- 操作回数制限（T=4000-64000）
- メモリ効率（20×20盤面）

## 期待スコア

- シンプル戦略: ベースライン
- 混色戦略: 30-50%改善
- 再利用戦略: さらに20-30%改善

## 次のアクション

1. シンプル戦略の実装から開始
2. サンプルケースでの動作確認
3. 段階的な改良実施
