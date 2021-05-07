[@react.component]
let make = (~comment: ConfessionData.confessionComment, ()) => {
  <b> {React.string(comment.message)} </b>;
};
