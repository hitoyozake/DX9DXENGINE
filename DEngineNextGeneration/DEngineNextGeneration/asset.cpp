#include "asset.h"
#include "directx.h"
#include "module.h"
#include "animation.h"

namespace asset
{
	using module::lexical_cast;
	void load_graph( std::vector< std::string > const & strs, std::map< std::string, int > & asset_map );
	
	//１行受け取り,区切りでパースして返す
	std::vector< std::string > graph_loader::parse( std::string const & str ) const
	{
		std::vector< std::string > result;

		boost::split( result, str, boost::is_any_of( "," ) );

		return result;
	}

	//ファイル名をもとに assetname-handleのmap作成まで全てを執り行う
	boost::optional< std::map< std::string, int > > graph_loader::load( std::string const & animlist_filename )
	{
		if( auto animlist = load_anim( animlist_filename ) )
		{
			std::map< std::string, int > graph_map;

			for( auto const & i : animlist.get() )
			{
				auto const parsed = parse( i );

				load_graph( parsed, graph_map );
			}

			return graph_map;
		}

		return boost::none;
	}


	//パースが済んだstrから画像などを読み込む
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

	//parseされたanimlist-stringをもとにファイルを開いて，各行をparseそて値に格納
	void anim_loader::register_anim( std::vector< std::string > const & strs, std::map< std::string, anim::animation > & map, std::map< std::string, int > const & graph_map )
	{
		using anim::animation;
		using anim::frame;

		if( strs.size() == 0 )
			return;
		animation anim;
		anim.asset_name = strs[ 0 ];

		for( int i = 1; i < strs.size(); ++i )
		{
			auto const parsed = parse( strs[ i ] );

			frame f;

			enum anim_format
			{
				assetname,
				type,
				x,
				y,
				time,
				r,
				g,
				b,
				a,
				scale,
				angle
			};

			f.x = lexical_cast< int >( parsed[ anim_format::x ] );
			f.y = lexical_cast< int >( parsed[ anim_format::y ] );
			f.r = lexical_cast< int >( parsed[ anim_format::r ] );
			f.g = lexical_cast< int >( parsed[ anim_format::g ] );
			f.b = lexical_cast< int >( parsed[ anim_format::b ] );
			f.a = lexical_cast< int >( parsed[ anim_format::a ] );
			f.angle = lexical_cast< double >( parsed[ anim_format::angle ] );
			f.scale = lexical_cast< double >( parsed[ anim_format::scale ] );
			f.time = lexical_cast< double >( parsed[ anim_format::time ] );
			f.type = lexical_cast< int >( parsed[ anim_format::type ] );
			f.graph_asset_name = parsed[ anim_format::assetname ];

			//prefetchをここで済ませたい．が，仕事し過ぎか?
			try
			{
				f.handle_ = graph_map.at( f.graph_asset_name );
			}
			catch( std::exception & e )
			{
				f.handle_ = 0;
			}

			anim.frames.push_back( f );

		}
		map[ anim.asset_name ] = anim;
	}

	//,区切りでparseする
	std::vector< std::string > anim_loader::parse( std::string const & str ) const
	{
		std::vector< std::string > result;

		boost::split( result, str, boost::is_any_of( "," ) );

		return result;
	}

	//animlistからanimファイル一覧を読み込む
	boost::optional< std::vector< std::string > > anim_loader::load_anim( std::string const & animlist_filename )
	{
		std::ifstream animlist( animlist_filename );

		if( !animlist )
		{
			return boost::none;
		}

		std::vector< std::string > contents;

		while( !animlist.eof() )
		{
			std::string tmp;
			std::getline( animlist, tmp );

			if( tmp[ 0 ] != '#' && tmp != "" )
				contents.push_back( tmp );
		}

		return boost::optional< std::vector< std::string > >( contents );
	}

	//ファイル名をもとに assetname-handleのmap作成まで全てを執り行う
	boost::optional< std::map< std::string, anim::animation > > anim_loader::load( std::string const & animlist_filename, std::map< std::string, int > const & graph_map )
	{
		if( auto animlist = load_anim( animlist_filename ) )
		{
			std::map< std::string, anim::animation > anim_map;

			for( auto const & i : animlist.get() )
			{
				auto const parsed = parse( i );

				if( parsed.size() != 2 )
					continue;

				std::vector< std::vector< std::string > > anims;

				std::ifstream ifs( parsed[ 1 ] );

				if( !ifs )
					continue;

				std::string tmp;

				while( !ifs.eof() )
				{
					std::getline( ifs, tmp );
					auto anim_parsed = parse( tmp );
					register_anim( anim_parsed, anim_map, graph_map );
				}


			}
			return anim_map;
		}

		return boost::none;
	}

}





