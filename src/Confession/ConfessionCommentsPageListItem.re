open Utils;

//this component has a teriable name and needs to be renamed

requireCSS("src/styles.css");

let commentIcon = requireAssetURI("src/Confession/comment.png");

[@react.component]
let make = (~confession: ConfessionData.confession, ()) => {
  let renderTitle = () => {
    //what title bitch, its a confession, rename this
    let content = React.string(confession.message);
    <div className="ConfessionListItem_flexRow">
      <div className="ConfessionListItem_storyCell">
        <header className="ConfessionCommentsPageListItem_storyTitle">
          content
        </header>
      </div>
    </div>;
  };

  let renderCommentsList = () =>
    <div>
      <h4 className="ConfessionListItem_commentRow">
        {React.string("Comments")}
      </h4>
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
    </div>;

  let renderNoCommentsMessage = () =>
    <div>
      <h4 className="ConfessionListItem_commentRow">
        {React.string("Be the first to leave a comment!")}
      </h4>
    </div>;

  <>
    <div className="ConfessionListItem_itemRow">
      <div className="ConfessionListItem_headingRow"> {renderTitle()} </div>
      {Array.length(confession.comments.commentsArray) > 0
         ? renderCommentsList() : renderNoCommentsMessage()}
    </div>
  </>;
  //this is only for the home page and has to be renamed
  //this component has a teriable name and needs to be renamed
};
