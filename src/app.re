[@react.component]
let make = () => {
  let url = ReasonReact.Router.useUrl();

  switch (url.path) {
  | [] => <RecentConfessionsPage />
  | ["submit"] => <SubmitPage />
  | ["comments", id] => <ConfessionCommentsPage id />
  | _ => <NotFound />
  };
};
