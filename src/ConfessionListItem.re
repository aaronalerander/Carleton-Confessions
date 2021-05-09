open Utils;

requireCSS("src/styles.css");

let commentIcon = requireAssetURI("src/comment.png");

[@react.component]
let make = (~confession: ConfessionData.confession, ~index: int, ()) => {
  let renderIndex = () =>
    <aside className="ConfessionListItem_storyIndex">
      {React.string(string_of_int(index + 1))}
    </aside>;

  let renderTitle = () => {
    let content = React.string(confession.message);
    <header className="ConfessionListItem_storyTitle">
      <Link
        href={"/comments/" ++ confession.id}
        className="ConfessionListItem_link">
        content
      </Link>
    </header>;
  };

  let renderArticleButton = () =>
    <div className="ConfessionListItem_flexRow">
      {renderIndex()}
      <div className="ConfessionListItem_storyCell"> {renderTitle()} </div>
    </div>;

  let renderCommentsButton = () =>
    <div className="ConfessionListItem_commentsCell">
      <Link
        href={"/comments/" ++ confession.id}
        className="ConfessionListItem_link">
        <div>
          <img
            alt="comments"
            className="ConfessionListItem_icon"
            src=commentIcon
          />
        </div>
        <div>
          <span className="ConfessionListItem_commentsText">
            {React.string(" View All Comments")}
          </span>
        </div>
      </Link>
    </div>;

  <>
    <div className="ConfessionListItem_itemRow">
      {renderArticleButton()}
      {renderCommentsButton()}
    </div>
    <b className="ConfessionListItem_commentRow">
      {React.string("Comments")}
    </b>
    <div>
      {confession.comments.commentsArray
       ->Belt.Array.map(item =>
           <span className="ConfessionListItem_commentRow" key={item.id}>
             {React.string("-" ++ item.message)}
           </span>
         )
       ->React.array}
      <br />
    </div>
  </>;
};
