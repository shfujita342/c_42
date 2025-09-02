・void *mlx_new_window(void *mlx_ptr, int width, int height, char *title);

mlx_ptr : mlx_init() の戻り値（MiniLibX の接続ハンドル）

width : ウィンドウの横幅（ピクセル単位）

height : ウィンドウの縦幅（ピクセル単位）

title : ウィンドウのタイトルバーに表示される文字列

戻り値は 作成されたウィンドウを表すポインタ（失敗したら NULL）。

・void *mlx_xpm_file_to_image(void *mlx_ptr,char *filename,int *width,int *height);

:MiniLibX に .xpm 形式の画像ファイルを読み込ませ、描画用の画像オブジェクトを作成する処理

mlx_ptr : mlx_init() で作った MLX ハンドル

filename : 読み込む .xpm ファイルのパス

width, height : 読み込んだ画像の横幅・縦幅を返す変数のポインタ

戻り値 : 読み込んだ画像を表すポインタ（失敗したら NULL）

mlx_init:Xサーバとの接続を開く（ディスプレイにアクセス可能な状態にする）
