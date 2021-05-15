open Utils;

requireCSS("src/styles.css");

let commentIcon = requireAssetURI("src/Components/images/comment.png");

[@react.component]
let make = (~confession: Types.confession, ~index: int, ()) => {
  let renderIndex = () =>
    <aside className="recentConfessionsListItemStoryIndex">
      {React.string(string_of_int(index + 1))}
    </aside>;

  let renderTitle = () => {
    let title = React.string(confession.message);
    <header className="recentConfessionsListItemStoryTitle">
      <Link
        href={"/comments/" ++ confession.id}
        className="recentConfessionsListItemLink">
        title
      </Link>
    </header>;
  };

  let renderConfessionTitle = () =>
    <div className="recentConfessionsListItemflexRow">
      {renderIndex()}
      <div className="recentConfessionsListItemStoryCell">
        {renderTitle()}
      </div>
    </div>;

  let renderCommentsButton = () =>
    <div className="recentConfessionsListItemCommentsCell">
      <Link
        href={"/comments/" ++ confession.id}
        className="recentConfessionsListItemLink">
        <div>
          <img
            alt="comments"
            className="recentConfessionsListItemIcon"
            src=commentIcon
          />
        </div>
        <div>
          <span className="recentConfessionsListItemCommentsText">
            {React.string("Comments")}
          </span>
        </div>
      </Link>
    </div>;

  let renderCommentsList = () =>
    <div>
      <h4 className="recentConfessionsListItemCommentRow">
        {React.string("First Comments")}
      </h4>
      <div>
        {confession.comments.commentsArray
         ->Belt.Array.map(item =>
             <span
               className="recentConfessionsListItemCommentRow" key={item.id}>
               {React.string("-" ++ item.message)}
             </span>
           )
         ->React.array}
        <br />
      </div>
    </div>;

  let renderNoCommentsMessage = () =>
    <div>
      <h4 className="recentConfessionsListItemCommentRow">
        {React.string("Be the first to leave a comment!")}
      </h4>
    </div>;

  <>
    <div className="recentConfessionsListItemItemRow">
      <div className="recentConfessionsListItemHeadingRow">
        {renderConfessionTitle()}
        {renderCommentsButton()}
      </div>
      {Array.length(confession.comments.commentsArray) > 0
         ? renderCommentsList() : renderNoCommentsMessage()}
    </div>
  </>;
};
