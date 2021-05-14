open Utils;

requireCSS("src/styles.css");

[@react.component]
let make = (~confession: ConfessionData.confession, ()) => {
  let renderTitle = () => {
    let content = React.string(confession.message);
    <div className="RecentConfessionsListItem_flexRow">
      <div className="RecentConfessionsListItem_storyCell">
        <h1 className="ConfessionPageListItem_storyTitle"> content </h1>
      </div>
    </div>;
  };

  let renderCommentsList = () =>
    <div>
      <h4 className="RecentConfessionsListItem_commentRow">
        {React.string("Comments")}
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
        {renderTitle()}
      </div>
      {Array.length(confession.comments.commentsArray) > 0
         ? renderCommentsList() : renderNoCommentsMessage()}
    </div>
  </>;
};
