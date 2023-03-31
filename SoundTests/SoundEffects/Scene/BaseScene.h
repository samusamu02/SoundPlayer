#pragma once
#include <memory>
#include "SceneID.h"

// エラー対策
class BaseScene;
using uniqueBase = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	// 初期化
	virtual void Init() = 0;

	/// <summary>
	/// 更新処理（次のシーンへ送る)
	/// </summary>
	/// <param name="ownScene">自分のシーン情報</param>
	/// <returns>自分のシーン情報を返す</returns>
	virtual uniqueBase Update(uniqueBase ownScene) = 0;

	// 描画処理
	virtual void Draw();

	// 自分のシーンでの描画処理
	virtual void DrawOwnScreen() = 0;

	// シーン情報取得
	virtual SceneID GetSceneID(void) = 0;
protected:
	// スクリーン情報
	int screenID_;
private:

};

