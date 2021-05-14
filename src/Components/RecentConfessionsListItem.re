open Utils;

requireCSS("src/styles.css");

let commentIcon = requireAssetURI("src/Components/images/comment.png");

[@react.component]
let make = (~confession: ConfessionData.confession, ~index: int, ()) => {
  let renderIndex = () =>
    <aside className="RecentConfessionsListItem_storyIndex">
      {React.string(string_of_int(index + 1))}
    </aside>;

  let renderTitle = () => {
    let title = React.string(confession.message);
    <header className="RecentConfessionsListItem_storyTitle">
      <Link
        href={"/comments/" ++ confession.id}
        className="RecentConfessionsListItem_link">
        title
      </Link>
    </header>;
  };

  let renderConfessionTitle = () =>
    <div className="RecentConfessionsListItem_flexRow">
      {renderIndex()}
      <div className="RecentConfessionsListItem_storyCell">
        {renderTitle()}
      </div>
    </div>;

  let renderCommentsButton = () =>
    <div className="RecentConfessionsListItem_commentsCell">
      <Link
        href={"/comments/" ++ confession.id}
        className="RecentConfessionsListItem_link">
        <div>
          <img
            alt="comments"
            className="RecentConfessionsListItem_icon"
            src=commentIcon
          />
        </div>
        <div>
          <span className="RecentConfessionsListItem_commentsText">
            {React.string("Comments")}
          </span>
        </div>
      </Link>
    </div>;

  let renderCommentsList = () =>
    <div>
      <h4 className="RecentConfessionsListItem_commentRow">
        {React.string("First Comments")}
      </h4>
      <div>
        {confession.comments.commentsArray
         ->Belt.Array.map(item =>
             <span
               className="RecentConfessionsListItem_commentRow" key={item.id}>
               {React.string("-" ++ item.message)}
             </span>
           )
         ->React.array}
        <br />
      </div>
    </div>;

  let renderNoCommentsMessage = () =>
    <div>
      <h4 className="RecentConfessionsListItem_commentRow">
        {React.string("Be the first to leave a comment!")}
      </h4>
    </div>;

  <>
    <div className="RecentConfessionsListItem_itemRow">
      <div className="RecentConfessionsListItem_headingRow">
        {renderConfessionTitle()}
        {renderCommentsButton()}
      </div>
      {Array.length(confession.comments.commentsArray) > 0
         ? renderCommentsList() : renderNoCommentsMessage()}
    </div>
  </>;
};
