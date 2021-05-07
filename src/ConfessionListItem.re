open Utils;

requireCSS("src/StoryListItem.css");

let commentIcon = requireAssetURI("src/comment.png");

[@react.component]
let make = (~confession: ConfessionData.confession, ~index: int, ()) => {
  let renderIndex = () =>
    <aside className="StoryListItem_storyIndex">
      {React.string(string_of_int(index + 1))}
    </aside>;

  let renderTitle = () => {
    let content = React.string(confession.message);
    <header className="StoryListItem_storyTitle">
      <Link
        href={"/comments/" ++ confession.id} className="StoryListItem_link">
        content
      </Link>
    </header>;
  };

  let renderArticleButton = () =>
    <div className="StoryListItem_flexRow">
      {renderIndex()}
      <div className="StoryListItem_storyCell"> {renderTitle()} </div>
    </div>;

  let renderCommentsButton = () =>
    <div className="StoryListItem_commentsCell">
      <Link
        href={"/comments/" ++ confession.id} className="StoryListItem_link">
        <div>
          <img alt="comments" className="StoryListItem_icon" src=commentIcon />
        </div>
        <div>
          <span className="StoryListItem_commentsText">
            {React.string(" View All Comments")}
          </span>
        </div>
      </Link>
    </div>;

  <>
    <div className="StoryListItem_itemRow">
      {renderArticleButton()}
      {renderCommentsButton()}
    </div>
    <b className="StoryListItem_commentRow"> {React.string("Comments")} </b>
    <div>
      {confession.comments.commentsArray
       ->Belt.Array.map(item
           //this will be changed to CommentListItemLater
           //<div className="StoryListItem_itemRow">
           =>
             <span className="StoryListItem_commentRow" key={item.id}>
               {React.string("-" ++ item.message)}
             </span>
           )
       //</div>
       ->React.array}
      <br />
    </div>
  </>;
};
