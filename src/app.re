[@react.component]
let make = () => {
  let url = ReasonReact.Router.useUrl();

  switch (url.path) {
  | ["submit"] => <SubmitConfessionPage />
  | ["comments", id] => <ConfessionPage id />
  | [] => <RecentConfessionsPage />
  | _ => <NotFoundPage />
  };
};
