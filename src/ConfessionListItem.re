open Utils;

requireCSS("src/StoryListItem.css");

let commentIcon = requireAssetURI("src/comment.png");

[@react.component]
let make = (~confession: ConfessionData.confession, ~index: int, ~showCommentInput = true, ()) => {
  let renderIndex = () =>
    <aside className="StoryListItem_storyIndex">
        {React.string(string_of_int(index + 1))}
    </aside>;
  let renderTitle = () => {
    let content = React.string(confession.message);
        <header className="StoryListItem_storyTitle">
            <Link href={"/comments/" ++ confession.id} className="StoryListItem_link" >
            content
            </Link>
        </header>;
  };
  let renderArticleButton = () =>
    <div className="StoryListItem_flexRow">
      {renderIndex()}
      <div className="StoryListItem_storyCell"> 
        {renderTitle()}
      </div>
    </div>;
  let renderCommentsButton = () =>
    <div className="StoryListItem_commentsCell">
      <Link
        href={"/comments/" ++ confession.id}
        className="StoryListItem_link">
        <div>
          <img alt="comments" className="StoryListItem_icon" src=commentIcon />
        </div>
        <div>
          <span className="StoryListItem_commentsText">
            {React.string(" comments")} 
          </span>
        </div>
      </Link>
    </div>;


  <>  
    {showCommentInput
      ? ReasonReact.string("this will be the send comment button")
      : ReasonReact.string("Change this to blank later")
    }
    <div className="StoryListItem_itemRow">

    {renderArticleButton()}
    {renderCommentsButton()}
    // <b>{React.string(confession.message)}</b>
    {
        {   
        confession.comments.commentsArray
            ->Belt.Array.map(item =>
                //this will be changed to CommentListItemLater
                <b key={item.id}> {React.string(item.message)} </b>
            )
            ->React.array
        }
        ;}
    </div>
    </>
};
