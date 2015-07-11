#include "asset.h"
#include "directx.h"

namespace anim
{
	//１行受け取り,区切りでパースして返す
	std::vector< std::string > graph_loader::parse( std::string const & str ) const
	{
		std::vector< std::string > result;

		boost::split( result, str, boost::is_any_of( "," ) );

		return result;
	}

	void load_graph( std::vector< std::string > const & strs, std::map< std::string, int > & asset_map )
	{
		enum graph_format
		{ 
			asset_name,
			graph_name,
			size
		};

		if( strs.size() != graph_format::size )
		{
			return;
		}

		//画像を読み込んで登録
		//directXへの登録(load_graphで登録される)
		//返ってくるのは現在のところginfoのvectorのインデックス
		auto const graph_handle = graphic_api::load_graph( strs[ graph_format::graph_name ] );

		//load_graphで読み込んだ画像ハンドルを読み出せるように
		//assetに登録( assetname - handle )のmapが作られる(※リソースの開放は自動でされる)
		asset_map[ strs[ graph_format::asset_name ] ] = graph_handle;
	}

	//"読み込む画像一覧"が記載されたファイルを読み込んで一行ずつvectorに格納して返す
	boost::optional< std::vector< std::string > > graph_loader::load_anim( std::string const & graphlist_filename )
	{
		std::ifstream graphlist( graphlist_filename );

		if( !graphlist )
		{
			return boost::none;
		}

		std::vector< std::string > contents;

		while( !graphlist.eof() )
		{
			std::string tmp;
			std::getline( graphlist, tmp );

			if( tmp[ 0 ] != '#' && tmp != "" )
				contents.push_back( tmp );
		}

		return boost::optional< std::vector< std::string > >( contents );
	}


}





