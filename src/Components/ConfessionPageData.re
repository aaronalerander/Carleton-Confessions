open Utils;

requireCSS("src/styles.css");

[@react.component]
let make = (~confession: ConfessionData.confession, ()) => {
  let renderTitle = () => {
    let content = React.string(confession.message);
    <div className="recentConfessionsListItemflexRow">
      <div className="recentConfessionsListItemStoryCell">
        <h1 className="ConfessionPageListItem_storyTitle"> content </h1>
      </div>
    </div>;
  };

  let renderCommentsList = () =>
    <div>
      <h4 className="recentConfessionsListItemCommentRow">
        {React.string("Comments")}
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
        {renderTitle()}
      </div>
      {Array.length(confession.comments.commentsArray) > 0
         ? renderCommentsList() : renderNoCommentsMessage()}
    </div>
  </>;
};
